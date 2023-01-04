#include "stack.hpp"

using namespace pandaboygba;

pbg_stack::pbg_stack(pbg_context *ctx)
  : _context_ptr(ctx)
{
  std::cout << "🎮 " << RED << "[" << ORANGE << "Running STACK!" << RED << "]" << DEFAULT << " 🎮" << std::endl;  
}

void pbg_stack::stack_push(uint8_t data) {
  this->_context_ptr->_cpu_ptr->cpu_get_regs()->sp--;
  this->_context_ptr->_bus_ptr->bus_write(this->_context_ptr->_cpu_ptr->cpu_get_regs()->sp, data);
}

void pbg_stack::stack_push16(uint16_t data) {
  //printf("SP = > %04X\n", this->_context_ptr->_cpu_ptr->cpu_get_regs()->sp);
  //printf("PC[data] = > %04X\n", data);
  this->stack_push((data >> 8) & 0xFF);
  this->stack_push(data & 0xFF);
  //printf("%d/%d\n", (data & 0xFF), ((data >> 8) & 0xFF));

}

uint8_t pbg_stack::stack_pop() {
  /*if (this->_context_ptr->_ui_ptr->_ticks > 986000 && 
    this->_context_ptr->_ui_ptr->_ticks < 986184
    ){
    printf("SP[%04X][%04X]\n", this->_context_ptr->_cpu_ptr->cpu_get_regs()->sp, this->_context_ptr->_bus_ptr->bus_read(this->_context_ptr->_cpu_ptr->cpu_get_regs()->sp));
    }*/
  return this->_context_ptr->_bus_ptr->bus_read(this->_context_ptr->_cpu_ptr->cpu_get_regs()->sp++);
}

uint16_t pbg_stack::stack_pop16() {
  uint16_t lo = this->stack_pop();
  uint16_t hi = this->stack_pop();
  return (hi << 8) | lo;
}
