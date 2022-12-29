#include "ram.hpp"

using namespace pandaboygba;

pbg_ram::pbg_ram (pbg_context *ctx)
  : _context_ptr(ctx)
{
}

uint8_t pbg_ram::wram_read(uint16_t address)
{
  address -= 0xC000;
  if (address >= 0x2000) {
    printf("INVALID WRAM ADDR %08X\n", address + 0xC000);
    exit(-1);
  }
  return this->wram[address];
}

void pbg_ram::wram_write(uint16_t address, uint8_t value)
{
  address -= 0xC000;
  this->wram[address] = value;
}

uint8_t pbg_ram::hram_read(uint16_t address)
{
  address -= 0xFF80;
  return this->hram[address];
}

void pbg_ram::hram_write(uint16_t address, uint8_t value)
{
  address -= 0xFF80;
  this->hram[address] = value;
}
