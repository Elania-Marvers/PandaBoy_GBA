#ifndef		___STACK_HPP___
#define		___STACK_HPP___
#include "common.hpp"
#include "context.hpp"


using namespace pandaboygba;
namespace pandaboygba
{
  class pbg_context;
  class  pbg_stack
  {
  private:
    pbg_context	*	_context_ptr;
  public:
    pbg_stack(pbg_context	*);

    void stack_push(uint8_t data);
    void stack_push16(uint16_t data);

    uint8_t stack_pop();
    uint16_t stack_pop16();
  };
}

#endif


/*
    STACK
    SP=0xDFFF
    MEMORY:
    0xDFF7: 00
    0xDFF8: 00
    0xDFF9: 00
    0xDFFA: 00
    0xDFFB: 00
    0xDFFC: 00
    0xDFFD: 00
    0xDFFE: 00
    0xDFFF: 00 <- SP
    PUSH 0x55
    SP-- = 0xDFFE
    MEMORY[0xDFFE] = 0x55
    MEMORY:
    0xDFF7: 00
    0xDFF8: 00
    0xDFF9: 00
    0xDFFA: 00
    0xDFFB: 00
    0xDFFC: 00
    0xDFFD: 00
    0xDFFE: 55 <- SP
    0xDFFF: 00
    PUSH 0x77
    SP-- = 0xDFFD
    MEMORY[0xDFFD] = 0x77
    MEMORY:
    0xDFF7: 00
    0xDFF8: 00
    0xDFF9: 00
    0xDFFA: 00
    0xDFFB: 00
    0xDFFC: 00
    0xDFFD: 77 <- SP
    0xDFFE: 55
    0xDFFF: 00
    val = POP
    val = MEMORY[0xDFFD] = 0x77
    SP++ = 0xDFFE
    MEMORY:
    0xDFF7: 00
    0xDFF8: 00
    0xDFF9: 00
    0xDFFA: 00
    0xDFFB: 00
    0xDFFC: 00
    0xDFFD: 77 
    0xDFFE: 55 <- SP
    0xDFFF: 00
    PUSH 0x88
    SP-- = 0xDFFD
    MEMORY[0xDFFD] = 0x88
    MEMORY:
    0xDFF7: 00
    0xDFF8: 00
    0xDFF9: 00
    0xDFFA: 00
    0xDFFB: 00
    0xDFFC: 00
    0xDFFD: 88 <- SP
    0xDFFE: 55 
    0xDFFF: 00
*/
