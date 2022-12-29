#include "ppu.hpp"

using namespace pandaboygba;

static pbg_ppu *ppu_ctx;

/*********************************************************/
/**	Those functions are constructor from the	**/
/**	pbg_ppu class					**/
/*********************************************************/

pbg_ppu::pbg_ppu(pbg_context *ctx)
  : _context_ptr(ctx)
{
  ppu_ctx = this;
}
/*
bool window_visible() {
  return LCDC_WIN_ENABLE && lcd_get_context()->win_x >= 0 &&
    lcd_get_context()->win_x <= 166 && lcd_get_context()->win_y >= 0 &&
    lcd_get_context()->win_y < YRES;
}

*/
pbg_ppu *ppu_get_context() {
    return ppu_ctx;
}
