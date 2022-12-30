#include "ppu.hpp"
#include "lcd.hpp"

using namespace pandaboygba;
pandaboygba::pbg_ppu *pandaboygba::ppu_get_context();
pandaboygba::pbg_lcd *pandaboygba::lcd_get_context();
  
bool pbg_ppu::window_visible()
{
  return LCDC_WIN_ENABLE && lcd_get_context()->win_x >= 0 && lcd_get_context()->win_x <= 166 && lcd_get_context()->win_y >= 0 && lcd_get_context()->win_y < YRES;
}

void pbg_ppu::pixel_fifo_push(uint32_t value)
{
}

uint32_t pbg_ppu::pixel_fifo_pop()
{
}

uint32_t pbg_ppu::fetch_sprite_pixels(int bit, uint32_t color, uint8_t bg_color)
{
}

bool pbg_ppu::pipeline_fifo_add()
{
}

void pbg_ppu::pipeline_load_sprite_tile()
{
}

void pbg_ppu::pipeline_load_sprite_data(uint8_t offset)
{
}

void pbg_ppu::pipeline_load_window_tile()
{
}

void pbg_ppu::pipeline_fetch()
{
}

void pbg_ppu::pipeline_push_pixel()
{
}

void pbg_ppu::pipeline_process()
{
}

void pbg_ppu::pipeline_fifo_reset()
{
}
