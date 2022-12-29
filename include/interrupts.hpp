#ifndef		___INTERRUPTS_HPP___
#define		___INTERRUPTS_HPP___
#include "context.hpp"
#include "stack.hpp"

using namespace pandaboygba;
namespace pandaboygba
{
  typedef enum {
    IT_VBLANK = 1,
    IT_LCD_STAT = 2,
    IT_TIMER = 4,
    IT_SERIAL = 8,
    IT_JOYPAD = 16
  } interrupt_type;
  /*
  void cpu_request_interrupt(interrupt_type t);
  void cpu_handle_interrupts(pbg_context *ctx);
  */
}

#endif
