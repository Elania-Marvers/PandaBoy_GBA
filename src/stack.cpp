#include "stack.hpp"

using namespace pandaboygba;

void pbg_stack::stack_push(uint8_t data) {
    cpu_get_regs()->sp--;
    bus_write(cpu_get_regs()->sp, data);
}

void pbg_stack::stack_push16(uint16_t data) {
  this->stack_push((data >> 8) & 0xFF);
  this->stack_push(data & 0xFF);
}

uint8_t pbg_stack::stack_pop() {
    return bus_read(cpu_get_regs()->sp++);
}

uint16_t pbg_stack::stack_pop16() {
    uint16_t lo = this->stack_pop();
    uint16_t hi = this->stack_pop();
    return (hi << 8) | lo;
}
