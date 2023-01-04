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
  std::cout << "🎮 " << RED << "[" << ORANGE << "Running PPU!" << RED << "]" << DEFAULT << " 🎮" << std::endl;
  ppu_ctx = this;
  this->current_frame = 0;
  this->line_ticks = 0;
  this->video_buffer = new uint32_t[YRES * XRES * sizeof(32)];
  this->pfc.line_x = 0;
  this->pfc.pushed_x = 0;
  this->pfc.fetch_x = 0;
  this->pfc.pixel_fifo.size = 0;
  this->pfc.pixel_fifo.head = this->pfc.pixel_fifo.tail = NULL;
  this->pfc.cur_fetch_state = FS_TILE;
  this->line_sprites = 0;
  this->fetched_entry_count = 0;
  this->window_line = 0;
  LCDS_MODE_SET(MODE_OAM);
  memset(this->oam_ram, 0, sizeof(this->oam_ram));
  memset(this->video_buffer, 0, YRES * XRES * sizeof(uint32_t));
  
}

pbg_ppu::~ pbg_ppu()
{
  delete this->video_buffer;
}

void pbg_ppu::ppu_tick() {
  this->line_ticks++;
  //  printf("LCDS MODE [%04X]\n", LCDS_MODE);
  switch(LCDS_MODE) {
  case MODE_OAM:
    this->ppu_mode_oam();
    break;
  case MODE_XFER:
    this->ppu_mode_xfer();
    break;
  case MODE_VBLANK:
    this->ppu_mode_vblank();
    break;
  case MODE_HBLANK:
    this->ppu_mode_hblank();
    break;
  }
}


void pbg_ppu::ppu_oam_write(uint16_t address, uint8_t value) {
  if (address >= 0xFE00)
    address -= 0xFE00;
  uint8_t *p = (uint8_t *) this->oam_ram;
  p[address] = value;
}

uint8_t pbg_ppu::ppu_oam_read(uint16_t address) {
  if (address >= 0xFE00)
    address -= 0xFE00;
  uint8_t *p = (uint8_t *) this->oam_ram;
  return p[address];
}

void pbg_ppu::ppu_vram_write(uint16_t address, uint8_t value) {
  this->vram[address - 0x8000] = value;
}

uint8_t pbg_ppu::ppu_vram_read(uint16_t address) {
  return this->vram[address - 0x8000];
}

pandaboygba::pbg_ppu *pandaboygba::ppu_get_context() {
  return ppu_ctx;
}
