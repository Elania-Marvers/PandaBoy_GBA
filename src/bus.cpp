#include "bus.hpp"


// 0x0000 - 0x3FFF : ROM Bank 0
// 0x4000 - 0x7FFF : ROM Bank 1 - Switchable
// 0x8000 - 0x97FF : CHR RAM
// 0x9800 - 0x9BFF : BG Map 1
// 0x9C00 - 0x9FFF : BG Map 2
// 0xA000 - 0xBFFF : Cartridge RAM
// 0xC000 - 0xCFFF : RAM Bank 0
// 0xD000 - 0xDFFF : RAM Bank 1-7 - switchable - Color only
// 0xE000 - 0xFDFF : Reserved - Echo RAM
// 0xFE00 - 0xFE9F : Object Attribute Memory
// 0xFEA0 - 0xFEFF : Reserved - Unusable
// 0xFF00 - 0xFF7F : I/O Registers
// 0xFF80 - 0xFFFE : Zero Page

using namespace pandaboygba;

uint8_t	pbg_bus::bus_read(uint16_t	address)
{
  if (address < 0x8000) 			//ROM Data
    return this->_context_ptr->_cart_ptr->cart_read(address);		// CART
  else if (address < 0xA000) 			//Char/Map Data
    return this->_context_ptr->_ppu_ptr->ppu_vram_read(address);	// PPU
  else if (address < 0xC000) 			//Cartridge RAM
    return this->_context_ptr->_cart_ptr->cart_read(address);
  else if (address < 0xE000) 			//WRAM (Working RAM)
    return this->_context_ptr->_ram_ptr->wram_read(address);		// RAM
  else if (address < 0xFE00) 			//reserved echo ram...
    return 0;
  else if (address < 0xFEA0) {			//OAM
    if (this->_context_ptr->_dma_ptr->dma_transferring())		// DMA
      return 0xFF;
    return this->_context_ptr->_ppu_ptr->ppu_oam_read(address);		// PPU
  } else if (address < 0xFF00) 			//reserved unusable...
    return 0;
  else if (address < 0xFF80) 			//IO Registers...
    return this->_context_ptr->_io_ptr->io_read(address);		// IO
  else if (address == 0xFFFF) 			//CPU ENABLE REGISTER...
    return this->_context_ptr->_cpu_ptr->cpu_get_ie_register();		// CPU
  return this->_context_ptr->_ram_ptr->hram_read(address);		// RAM
}

void	pbg_bus::bus_write(uint16_t	address,
			   uint8_t	value)
{
  if (address < 0x8000) 		//ROM Data
    this->_context_ptr->_cart_ptr->cart_write(address, value);
  else if (address < 0xA000) 		//Char/Map Data
    this->_context_ptr->_ppu_ptr->ppu_vram_write(address, value);
  else if (address < 0xC000)		//EXT-RAM
    this->_context_ptr->_cart_ptr->cart_write(address, value);
  else if (address < 0xE000)		//WRAM
    this->_context_ptr->_ram_ptr->wram_write(address, value);
  else if (address < 0xFE00) {		//reserved echo ram
  } else if (address < 0xFEA0) {	//OAM
    if (this->_context_ptr->_dma_ptr->dma_transferring()) {
      return;
    }
    this->_context_ptr->_ppu_ptr->ppu_oam_write(address, value);
  } else if (address < 0xFF00) {	//unusable reserved
  } else if (address < 0xFF80)		//IO Registers...
    this->_context_ptr->_io_ptr->io_write(address, value);
  else if (address == 0xFFFF)		//CPU SET ENABLE REGISTER
    this->_context_ptr->_cpu_ptr->cpu_set_ie_register(value);
  else 
    this->_context_ptr->_ram_ptr->hram_write(address, value);
}


uint8_t	pbg_bus::bus_read16	(uint16_t	address)
{
  uint16_t lo = this->bus_read(address);
  uint16_t hi = this->bus_read(address + 1);
  return lo | (hi << 8);
}

void	pbg_bus::bus_write16	(uint16_t	address,
				 uint16_t	value)
{
  this->bus_write(address + 1, (value >> 8) & 0xFF);
  this->bus_write(address, value & 0xFF);
}
