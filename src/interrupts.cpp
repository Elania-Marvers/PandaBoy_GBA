#include "interrupts.hpp"

using namespace pandaboygba;


pbg_interrupts::pbg_interrupts(pbg_context *ctx)
  : _context_ptr(ctx)
{
  
}


void pbg_interrupts::int_handle(uint16_t address)
{
  this->_context_ptr->_stack_ptr->stack_push16(this->_context_ptr->_cpu_ptr->_regs.pc);
  this->_context_ptr->_cpu_ptr->_regs.pc = address;
}


bool pbg_interrupts::int_check(uint16_t address, interrupt_type it)
{
  if (this->_context_ptr->_cpu_ptr->_int_flags & it && this->_context_ptr->_cpu_ptr->_ie_register & it)
    {
      int_handle(address);
      this->_context_ptr->_cpu_ptr->_int_flags &= ~it;
      this->_context_ptr->_cpu_ptr->_halted = false;
      this->_context_ptr->_cpu_ptr->_int_master_enabled = false;
      return true;
    }
  return false;
}

void pbg_interrupts::cpu_handle_interrupts()
{
  if (int_check(0x40, IT_VBLANK)) {
    
  } else if (int_check(0x48, IT_LCD_STAT)) {
    
  } else if (int_check(0x50, IT_TIMER)) {
    
  }  else if (int_check(0x58, IT_SERIAL)) {
    
  }  else if (int_check(0x60, IT_JOYPAD)) {

  } 
}
