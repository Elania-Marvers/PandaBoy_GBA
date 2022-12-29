#ifndef		___CONTEXT_HPP___
#define		___CONTEXT_HPP___
#include "common.hpp"

namespace pandaboygba
{
  class pbg_cpu;
  class pbg_ppu;
  class pbg_io;
  class pbg_ram;
  class pbg_stack;
  class pbg_bus;
  class pbg_timer;
  class pbg_dma;
  class pbg_cart;
  class pbg_instruction;
  
  class pbg_context
  {
  public:
    pbg_cpu *		_cpu_ptr;
    pbg_bus *		_bus_ptr;
    pbg_cart *		_cart_ptr;
    pbg_ram *		_ram_ptr;
    pbg_io *		_io_ptr;
    pbg_ppu *		_ppu_ptr;
    pbg_dma *		_dma_ptr;
    pbg_timer *		_timer_ptr;
    pbg_instruction *	_instruction_ptr;
    pandaboygba::pbg_stack *		_stack_ptr;
    
  };
}
  
#endif
