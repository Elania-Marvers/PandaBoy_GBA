#include "context.hpp"

using namespace pandaboygba;

pbg_context::pbg_context()
{
  this->_cpu_ptr = new pbg_cpu(this);
  this->_bus_ptr = new pbg_bus(this);
  this->_cart_ptr = new pbg_cart(this);
  this->_ram_ptr = new pbg_ram(this);
  this->_io_ptr = new pbg_io(this);
  this->_ppu_ptr = new pbg_ppu(this);
  this->_dma_ptr = new pbg_dma(this);
  this->_timer_ptr = new pbg_timer(this);
  this->_instruction_ptr = new pbg_instruction(this);
  this->_stack_ptr = new pbg_stack(this);
  this->_lcd_ptr = new pbg_lcd(this);
  this->_gamepad_ptr = new pbg_gamepad(this);
}

pbg_context::~pbg_context()
{
  delete this->_cpu_ptr;
  delete this->_bus_ptr;
  delete this->_cart_ptr;
  delete this->_ram_ptr;
  delete this->_io_ptr;
  delete this->_ppu_ptr;
  delete this->_dma_ptr;
  delete this->_timer_ptr;
  delete this->_instruction_ptr;
  delete this->_stack_ptr;
  delete this->_lcd_ptr;
  delete this->_gamepad_ptr;
}
