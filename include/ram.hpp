#ifndef		___RAM_HPP___
#define		___RAM_HPP___
#include "common.hpp"
#include "context.hpp"

using namespace pandaboygba; 
namespace pandaboygba
{
  class pbg_context;

  class  pbg_ram
  {
  private:
    pbg_context	*	_context_ptr;
    uint8_t wram[0x2000];
    uint8_t hram[0x80];
    
  public:
    pbg_ram(pbg_context	*);
    uint8_t wram_read(uint16_t address);
    void wram_write(uint16_t address, uint8_t value);
    uint8_t hram_read(uint16_t address);
    void hram_write(uint16_t address, uint8_t value);
  };
}

#endif
