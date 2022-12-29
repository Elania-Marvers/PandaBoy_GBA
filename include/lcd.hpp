#ifndef		___LCD_HPP___
#define		___LCD_HPP___
#include "common.hpp"
#include "context.hpp"

#define LCDC_BGW_ENABLE (BIT(lcd_get_context()->lcdc, 0))
#define LCDC_OBJ_ENABLE (BIT(lcd_get_context()->lcdc, 1))
#define LCDC_OBJ_HEIGHT (BIT(lcd_get_context()->lcdc, 2) ? 16 : 8)
#define LCDC_BG_MAP_AREA (BIT(lcd_get_context()->lcdc, 3) ? 0x9C00 : 0x9800)
#define LCDC_BGW_DATA_AREA (BIT(lcd_get_context()->lcdc, 4) ? 0x8000 : 0x8800)
#define LCDC_WIN_ENABLE (BIT(lcd_get_context()->lcdc, 5))
#define LCDC_WIN_MAP_AREA (BIT(lcd_get_context()->lcdc, 6) ? 0x9C00 : 0x9800)
#define LCDC_LCD_ENABLE (BIT(lcd_get_context()->lcdc, 7))

#define LCDS_MODE ((lcd_mode)(lcd_get_context()->lcds & 0b11))
#define LCDS_MODE_SET(mode) { lcd_get_context()->lcds &= ~0b11; lcd_get_context()->lcds |= mode; }

#define LCDS_LYC (BIT(lcd_get_context()->lcds, 2))
#define LCDS_LYC_SET(b) (BIT_SET(lcd_get_context()->lcds, 2, b))
#define LCDS_STAT_INT(src) (lcd_get_context()->lcds & src)



using namespace pandaboygba;
namespace pandaboygba
{
  
  class pbg_context;
  class  pbg_lcd
  {
  private:
    pbg_context *		_context_ptr;

  public:
    //registers...
    uint8_t lcdc;
    uint8_t lcds;
    uint8_t scroll_y;
    uint8_t scroll_x;
    uint8_t ly;
    uint8_t ly_compare;
    uint8_t dma;
    uint8_t bg_palette;
    uint8_t obj_palette[2];
    uint8_t win_y;
    uint8_t win_x;

    //other data...
    uint32_t bg_colors[4];
    uint32_t sp1_colors[4];
    uint32_t sp2_colors[4];
    
  public:
    pbg_lcd(pbg_context *);
    uint8_t lcd_read(uint16_t address);
    void lcd_write(uint16_t address, uint8_t value);
    void update_palette(uint8_t palette_data, uint8_t pal);
    
  };

  pbg_lcd *lcd_get_context();
  
}

#endif
