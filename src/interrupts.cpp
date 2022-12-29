#include "interrupts.hpp"

using namespace pandaboygba;

void int_handle(pbg_context *ctx, uint16_t address)
{
  /*
    stack_push16(ctx->_cpu_ptr->_regs.pc);
    ctx->_cpu_ptr->_regs.pc = address;
  */
}


bool int_check(pbg_context *ctx, uint16_t address, interrupt_type it) {
  /*
  if (ctx->_cpu_ptr->_int_flags & it && ctx->_cpu_ptr->_ie_register & it) {
        int_handle(ctx, address);
        ctx->_cpu_ptr->_int_flags &= ~it;
        ctx->_cpu_ptr->_halted = false;
        ctx->_cpu_ptr->_int_master_enabled = false;
        return true;
    }
    return false;
  */
}

void cpu_request_interrupt(interrupt_type t)
{
  
}

void cpu_handle_interrupts(pbg_context *ctx)
{
  if (int_check(ctx, 0x40, IT_VBLANK)) {
    
  } else if (int_check(ctx, 0x48, IT_LCD_STAT)) {
    
  } else if (int_check(ctx, 0x50, IT_TIMER)) {
    
  }  else if (int_check(ctx, 0x58, IT_SERIAL)) {
    
  }  else if (int_check(ctx, 0x60, IT_JOYPAD)) {

  } 
}
