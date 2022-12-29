#ifndef		___CONTEXT_HPP___
#define		___CONTEXT_HPP___
#include "common.hpp"
#include "cart.hpp"
#include "ram.hpp"
#include "cpu.hpp"
#include "io.hpp"
#include "ppu.hpp"
#include "dma.hpp"
#include "timer.hpp"
#include "instruction.hpp"

namespace pandaboygba
{
  class  pbg_context
  {
  public:
    pbg_cart *		_cart_ptr;
    pbg_ram *		_ram_ptr;
    pbg_cpu *		_cpu_ptr;
    pbg_io *		_io_ptr;
    pbg_ppu *		_ppu_ptr;
    pbg_dma *		_dma_ptr;
    pbg_timer *		_timer_ptr;
    pbg_instruction *	_instruction_ptr;
  };
}

#endif
