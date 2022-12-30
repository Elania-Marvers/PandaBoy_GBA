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
}

void pbg_ppu::ppu_tick() {
  this->line_ticks++;
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
