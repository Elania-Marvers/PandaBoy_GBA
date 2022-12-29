#include "stack.hpp"

using namespace pandaboygba;

pbg_stack::pbg_stack(pbg_context *ctx)
  : _context_ptr(ctx)
{
  
}

void pbg_stack::stack_push(uint8_t data) {
  //    this->_context_ptr->_cpu_ptr->cpu_get_regs()->sp--;
  //    this->_context_ptr->_bus_ptr->bus_write(this->_context_ptr->_cpu_ptr->cpu_get_regs()->sp, data);
}

void pbg_stack::stack_push16(uint16_t data) {
  this->stack_push((data >> 8) & 0xFF);
  this->stack_push(data & 0xFF);
}

uint8_t pbg_stack::stack_pop() {
  //    return this->_context_ptr->_bus_ptr->bus_read(this->_context_ptr->_cpu_ptr->cpu_get_regs()->sp++);
}

uint16_t pbg_stack::stack_pop16() {
    uint16_t lo = this->stack_pop();
    uint16_t hi = this->stack_pop();
    return (hi << 8) | lo;
}
