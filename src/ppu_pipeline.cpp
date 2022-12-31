#include "ppu.hpp"

using namespace pandaboygba;
pandaboygba::pbg_ppu *pandaboygba::ppu_get_context();
pandaboygba::pbg_lcd *pandaboygba::lcd_get_context();
  
bool pbg_ppu::window_visible()
{
  return LCDC_WIN_ENABLE && lcd_get_context()->win_x >= 0 && lcd_get_context()->win_x <= 166 && lcd_get_context()->win_y >= 0 && lcd_get_context()->win_y < YRES;
}

void pbg_ppu::pixel_fifo_push(uint32_t value)
{
  fifo_entry *next = new fifo_entry;
  next->next = NULL;
  next->value = value;
  if (!ppu_get_context()->pfc.pixel_fifo.head)
    //first entry...
    ppu_get_context()->pfc.pixel_fifo.head = ppu_get_context()->pfc.pixel_fifo.tail = next;    //first entry...
  else
    {
      ppu_get_context()->pfc.pixel_fifo.tail->next = next;
      ppu_get_context()->pfc.pixel_fifo.tail = next;
    }
  ppu_get_context()->pfc.pixel_fifo.size++;
}

uint32_t pbg_ppu::pixel_fifo_pop()
{
  if (ppu_get_context()->pfc.pixel_fifo.size <= 0)
    {
      fprintf(stderr, "ERR IN PIXEL FIFO!\n");
      exit(-8);
    }
  fifo_entry *popped = ppu_get_context()->pfc.pixel_fifo.head;
  ppu_get_context()->pfc.pixel_fifo.head = popped->next;
  ppu_get_context()->pfc.pixel_fifo.size--;
  uint32_t val = popped->value;
  delete popped;
  return val;  
}

uint32_t pbg_ppu::fetch_sprite_pixels(int bit, uint32_t color, uint8_t bg_color)
{
  for (int i = 0; i < ppu_get_context()->fetched_entry_count; i++)
    {
      int sp_x = (ppu_get_context()->fetched_entries[i].x - 8) + ((lcd_get_context()->scroll_x % 8));
      if (sp_x + 8 < ppu_get_context()->pfc.fifo_x)  //past pixel point already...
	  continue;
      int offset = ppu_get_context()->pfc.fifo_x - sp_x;
      if (offset < 0 || offset > 7) 	//out of bounds..
	continue;
      bit = (7 - offset);
      if (ppu_get_context()->fetched_entries[i].f_x_flip)
	bit = offset;
      uint8_t hi = !!(ppu_get_context()->pfc.fetch_entry_data[i * 2] & (1 << bit));
      uint8_t lo = !!(ppu_get_context()->pfc.fetch_entry_data[(i * 2) + 1] & (1 << bit)) << 1;
      bool bg_priority = ppu_get_context()->fetched_entries[i].f_bgp;
      if (!(hi|lo))   //transparent
	continue;
      if (!bg_priority || bg_color == 0)
	{
	  color = (ppu_get_context()->fetched_entries[i].f_pn) ? 
	    lcd_get_context()->sp2_colors[hi|lo] : lcd_get_context()->sp1_colors[hi|lo];
	  if (hi|lo)
	    break;
	}
    }
  return color;
}

bool pbg_ppu::pipeline_fifo_add()
{
  if (ppu_get_context()->pfc.pixel_fifo.size > 8)         //fifo is full!
    return false;
  int x = ppu_get_context()->pfc.fetch_x - (8 - (lcd_get_context()->scroll_x % 8));
  for (int i=0; i<8; i++) {
    int bit = 7 - i;
    uint8_t hi = !!(ppu_get_context()->pfc.bgw_fetch_data[1] & (1 << bit));
    uint8_t lo = !!(ppu_get_context()->pfc.bgw_fetch_data[2] & (1 << bit)) << 1;
    uint32_t color = lcd_get_context()->bg_colors[hi | lo];
    if (!LCDC_BGW_ENABLE) 
      color = lcd_get_context()->bg_colors[0];
    if (LCDC_OBJ_ENABLE) 
      color = fetch_sprite_pixels(bit, color, hi | lo);
    if (x >= 0)
      {
	pixel_fifo_push(color);
	ppu_get_context()->pfc.fifo_x++;
      }
  }
  return true;
}

void pbg_ppu::pipeline_load_sprite_tile()
{
  oam_line_entry *le = ppu_get_context()->line_sprites;
  while(le)
    {
      int sp_x = (le->entry.x - 8) + (lcd_get_context()->scroll_x % 8);
      if ((sp_x >= ppu_get_context()->pfc.fetch_x && sp_x < ppu_get_context()->pfc.fetch_x + 8) || ((sp_x + 8) >= ppu_get_context()->pfc.fetch_x && (sp_x + 8) < ppu_get_context()->pfc.fetch_x + 8))             //need to add entry
	ppu_get_context()->fetched_entries[ppu_get_context()->fetched_entry_count++] = le->entry;
      le = le->next;
      if (!le || ppu_get_context()->fetched_entry_count >= 3)             //max checking 3 sprites on pixels
	break;
    }
}

void pbg_ppu::pipeline_load_sprite_data(uint8_t offset)
{
  int cur_y = lcd_get_context()->ly;
  uint8_t sprite_height = LCDC_OBJ_HEIGHT;
  for (int i = 0; i < ppu_get_context()->fetched_entry_count; i++)
    {
      uint8_t ty = ((cur_y + 16) - ppu_get_context()->fetched_entries[i].y) * 2;
      if (ppu_get_context()->fetched_entries[i].f_y_flip)       //flipped upside down...
	ty = ((sprite_height * 2) - 2) - ty;
      uint8_t tile_index = ppu_get_context()->fetched_entries[i].tile;
      if (sprite_height == 16) 
	tile_index &= ~(1); //remove last bit...
      ppu_get_context()->pfc.fetch_entry_data[(i * 2) + offset] = this->_context_ptr->_bus_ptr->bus_read(0x8000 + (tile_index * 16) + ty + offset);
    }
}

void pbg_ppu::pipeline_load_window_tile()
{
  if (!this->window_visible())
    return;
  uint8_t window_y = lcd_get_context()->win_y;
  if (ppu_get_context()->pfc.fetch_x + 7 >= lcd_get_context()->win_x && ppu_get_context()->pfc.fetch_x + 7 < lcd_get_context()->win_x + YRES + 14)
    {
      if (lcd_get_context()->ly >= window_y && lcd_get_context()->ly < window_y + XRES)
	{
	  uint8_t w_tile_y = ppu_get_context()->window_line / 8;
	  ppu_get_context()->pfc.bgw_fetch_data[0] = this->_context_ptr->_bus_ptr->bus_read(LCDC_WIN_MAP_AREA + ((ppu_get_context()->pfc.fetch_x + 7 - lcd_get_context()->win_x) / 8) + (w_tile_y * 32));
	  if (LCDC_BGW_DATA_AREA == 0x8800) 
	    ppu_get_context()->pfc.bgw_fetch_data[0] += 128;
	}
    }
}

void pbg_ppu::pipeline_fetch()
{
  switch(ppu_get_context()->pfc.cur_fetch_state) {
  case FS_TILE: {
    ppu_get_context()->fetched_entry_count = 0;
    if (LCDC_BGW_ENABLE)
      {
	ppu_get_context()->pfc.bgw_fetch_data[0] = this->_context_ptr->_bus_ptr->bus_read(LCDC_BG_MAP_AREA + (ppu_get_context()->pfc.map_x / 8) + (((ppu_get_context()->pfc.map_y / 8)) * 32));
	if (LCDC_BGW_DATA_AREA == 0x8800)
	  ppu_get_context()->pfc.bgw_fetch_data[0] += 128;
	this->pipeline_load_window_tile();
      }
    if (LCDC_OBJ_ENABLE && ppu_get_context()->line_sprites) 
      this->pipeline_load_sprite_tile();
    ppu_get_context()->pfc.cur_fetch_state = FS_DATA0;
    ppu_get_context()->pfc.fetch_x += 8;
  } break;
  case FS_DATA0: {
    ppu_get_context()->pfc.bgw_fetch_data[1] = this->_context_ptr->_bus_ptr->bus_read(LCDC_BGW_DATA_AREA + (ppu_get_context()->pfc.bgw_fetch_data[0] * 16) + ppu_get_context()->pfc.tile_y);
    this->pipeline_load_sprite_data(0);
    ppu_get_context()->pfc.cur_fetch_state = FS_DATA1;
  } break;
  case FS_DATA1: {
    ppu_get_context()->pfc.bgw_fetch_data[2] = this->_context_ptr->_bus_ptr->bus_read(LCDC_BGW_DATA_AREA + (ppu_get_context()->pfc.bgw_fetch_data[0] * 16) + ppu_get_context()->pfc.tile_y + 1);
    this->pipeline_load_sprite_data(1);
    ppu_get_context()->pfc.cur_fetch_state = FS_IDLE;
  } break;
  case FS_IDLE: {
    ppu_get_context()->pfc.cur_fetch_state = FS_PUSH;
  } break;
  case FS_PUSH: {
    if (this->pipeline_fifo_add())
      ppu_get_context()->pfc.cur_fetch_state = FS_TILE;
  } break;
  }
}

void pbg_ppu::pipeline_push_pixel()
{
  if (ppu_get_context()->pfc.pixel_fifo.size > 8)
    {
      uint32_t pixel_data = this->pixel_fifo_pop();
      if (ppu_get_context()->pfc.line_x >= (lcd_get_context()->scroll_x % 8))
	{
	  ppu_get_context()->video_buffer[ppu_get_context()->pfc.pushed_x + (lcd_get_context()->ly * XRES)] = pixel_data;
	  ppu_get_context()->pfc.pushed_x++;
        }
      ppu_get_context()->pfc.line_x++;
    }
}

void pbg_ppu::pipeline_process()
{
  ppu_get_context()->pfc.map_y = (lcd_get_context()->ly + lcd_get_context()->scroll_y);
  ppu_get_context()->pfc.map_x = (ppu_get_context()->pfc.fetch_x + lcd_get_context()->scroll_x);
  ppu_get_context()->pfc.tile_y = ((lcd_get_context()->ly + lcd_get_context()->scroll_y) % 8) * 2;
  if (!(ppu_get_context()->line_ticks & 1))
    this->pipeline_fetch();
  this->pipeline_push_pixel();
}

void pbg_ppu::pipeline_fifo_reset()
{
  while(ppu_get_context()->pfc.pixel_fifo.size)
    this->pixel_fifo_pop();
  ppu_get_context()->pfc.pixel_fifo.head = 0;
}
