#ifndef		___INTERRUPTS_HPP___
#define		___INTERRUPTS_HPP___
#include "context.hpp"
#include "stack.hpp"

using namespace pandaboygba;
namespace pandaboygba
{

  class pbg_interrupts
  {
  private:
    pbg_context *_context_ptr;
  public:
    pbg_interrupts(pbg_context *);
    bool int_check(uint16_t address, interrupt_type it);
    void cpu_request_interrupt(interrupt_type t);
    void cpu_handle_interrupts();
    void int_handle(uint16_t address);
  };
}

#endif
