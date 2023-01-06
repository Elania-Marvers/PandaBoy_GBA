#include "io.hpp"

using namespace pandaboygba;

static char serial_data[2];

pbg_io::pbg_io(pbg_context *ctx)
  : _context_ptr(ctx)
{
  std::cout << "🎮 " << RED << "[" << ORANGE << "Running IO!" << RED << "]" << DEFAULT << " 🎮" << std::endl;  
}

uint8_t pbg_io::io_read(uint16_t address) {
  if (address == 0xFF00)
    return this->_context_ptr->_gamepad_ptr->gamepad_get_output();
  if (address == 0xFF01)
    return serial_data[0];
  if (address == 0xFF02)
    return serial_data[1];
  if (BETWEEN(address, 0xFF04, 0xFF07))
    return this->_context_ptr->_timer_ptr->timer_read(address);
  if (address == 0xFF0F)
    return this->_context_ptr->_cpu_ptr->cpu_get_int_flags();
  if (BETWEEN(address, 0xFF10, 0xFF3F))
    return 0; // ignore sound
  if (BETWEEN(address, 0xFF40, 0xFF4B))
    return this->_context_ptr->_lcd_ptr->lcd_read(address);
  printf("UNSUPPORTED bus_read(%04X)\n", address);
  return 0;
}

void pbg_io::io_write(uint16_t address, uint8_t value) {
  if (address == 0xFF00) {
    this->_context_ptr->_gamepad_ptr->gamepad_set_sel(value);
    return;
  }
  if (address == 0xFF01) {
    serial_data[0] = value;
    return;
  }
  if (address == 0xFF02) {
    serial_data[1] = value;
    return;
  }
  if (BETWEEN(address, 0xFF04, 0xFF07)) {
    this->_context_ptr->_timer_ptr->timer_write(address, value);
    return;
  }
  if (address == 0xFF0F) {
    this->_context_ptr->_cpu_ptr->cpu_set_int_flags(value);
    return;
  }
  if (BETWEEN(address, 0xFF10, 0xFF3F)) {
    return; // ignore sound
  }
  if (BETWEEN(address, 0xFF40, 0xFF4B)) {
    this->_context_ptr->_lcd_ptr->lcd_write(address, value);
    return;
  }
  printf("UNSUPPORTED bus_write(%04X)\n", address);
}
