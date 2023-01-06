#include "lcd.hpp"

using namespace pandaboygba;

static pbg_lcd *lcd_ctx;
static unsigned long colors_default[4] = {0xFFFFFFFF, 0xFFAAAAAA, 0xFF555555, 0xFF000000}; 

pbg_lcd::pbg_lcd(pbg_context *ctx)
  : _context_ptr(ctx)
{
  std::cout << "🎮 " << RED << "[" << ORANGE << "Running LCD!" << RED << "]" << DEFAULT << " 🎮" << std::endl;
  lcd_ctx = this;

  this->lcdc = 0x91;
  this->scroll_x = 0x00;
  this->scroll_y = 0x00;
  this->ly = 0x00;
  this->ly_compare = 0x00;
  this->bg_palette = 0xFC;
  this->obj_palette[0] = 0xFF;
  this->obj_palette[1] = 0xFF;
  this->win_y = 0x00;
  this->win_x = 0x00;
  for (int i = 0; i < 4; i++) {
    this->bg_colors[i] = colors_default[i];
    this->sp1_colors[i] = colors_default[i];
    this->sp2_colors[i] = colors_default[i];
  }
  
}

uint8_t pbg_lcd::lcd_read(uint16_t address)
{
  uint8_t offset = (address - 0xFF40);
  uint8_t *p = (uint8_t *) lcd_ctx;
  return p[offset];  
}

void pbg_lcd::lcd_write(uint16_t address, uint8_t value)
{
  uint8_t offset = (address - 0xFF40);
  uint8_t *p = (uint8_t *) lcd_ctx;
  p[offset] = value;
  if (offset == 6)
    this->_context_ptr->_dma_ptr->dma_start(value);    //0xFF46 = DMA
  if (address == 0xFF47)
    this->update_palette(value, 0);
  else if (address == 0xFF48)
    this->update_palette(value & 0b11111100, 1);
  else if (address == 0xFF49)
    this->update_palette(value & 0b11111100, 2);
}

void pbg_lcd::update_palette(uint8_t palette_data, uint8_t pal)
{
  uint32_t *p_colors = this->bg_colors;
  if (pal == 1)
    p_colors = this->sp1_colors;
  else if (pal == 2)
    p_colors = this->sp2_colors;
  p_colors[0] = colors_default[palette_data & 0b11];
  p_colors[1] = colors_default[(palette_data >> 2) & 0b11];
  p_colors[2] = colors_default[(palette_data >> 4) & 0b11];
  p_colors[3] = colors_default[(palette_data >> 6) & 0b11];
}

pandaboygba::pbg_lcd *pandaboygba::lcd_get_context()
{
  return lcd_ctx;
}
