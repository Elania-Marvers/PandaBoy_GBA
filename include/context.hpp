#ifndef		___CONTEXT_HPP___
#define		___CONTEXT_HPP___
#include "common.hpp"
#include "emu.hpp"

#include "cpu.hpp"
#include "bus.hpp"
#include "cart.hpp"
#include "ram.hpp"
#include "io.hpp"
#include "ppu.hpp"
#include "dma.hpp"
#include "timer.hpp"
#include "instruction.hpp"
#include "stack.hpp"
#include "lcd.hpp"
#include "gamepad.hpp"
#include "dbg.hpp"
#include "interrupts.hpp"
#include "ui.hpp"

namespace pandaboygba
{
  class gba_emulator;
  class pbg_cpu;
  class pbg_bus;
  class pbg_cart;
  class pbg_ram;
  class pbg_io;
  class pbg_ppu;
  class pbg_dma;
  class pbg_timer;
  class pbg_instruction;
  class pbg_stack;
  class pbg_lcd;
  class pbg_gamepad;
  class pbg_dbg;
  class pbg_interrupts;
  class pbg_ui;
  
  class pbg_context
  {
  public:
    pbg_context(gba_emulator *);
    ~pbg_context();
    gba_emulator *	_emu_ptr;
    pbg_cpu *		_cpu_ptr;
    pbg_bus *		_bus_ptr;
    pbg_cart *		_cart_ptr;
    pbg_ram *		_ram_ptr;
    pbg_io *		_io_ptr;
    pbg_ppu *		_ppu_ptr;
    pbg_dma *		_dma_ptr;
    pbg_timer *		_timer_ptr;
    pbg_instruction *	_instruction_ptr;
    pbg_stack *		_stack_ptr;
    pbg_lcd *		_lcd_ptr;
    pbg_gamepad *	_gamepad_ptr;
    pbg_dbg *		_dbg_ptr;
    pbg_interrupts *	_interrupts_ptr;
    pbg_ui *		_ui_ptr;
  };
}
  
#endif
