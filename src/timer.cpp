#include "timer.hpp"

using namespace pandaboygba;

/*********************************************************/
/**	Those functions are constructor from the	**/
/**	pbg_timer class					**/
/*********************************************************/

pbg_timer::pbg_timer(pbg_context *ctx)
  : _context_ptr(ctx), _div(0xAC00)
{
  std::cout << "🎮 " << RED << "[" << ORANGE << "Running TIMER!" << RED << "]" << DEFAULT << " 🎮" << std::endl;
}

void pbg_timer::timer_tick()
{
  uint16_t prev_div = this->_div;
  bool timer_update = false;
  this->_div++;
  switch(this->_tac & (0b11)) {
  case 0b00:
    timer_update = (prev_div & (1 << 9)) && (!(this->_div & (1 << 9)));
    break;
  case 0b01:
    timer_update = (prev_div & (1 << 3)) && (!(this->_div & (1 << 3)));
    break;
  case 0b10:
    timer_update = (prev_div & (1 << 5)) && (!(this->_div & (1 << 5)));
    break;
  case 0b11:
    timer_update = (prev_div & (1 << 7)) && (!(this->_div & (1 << 7)));
    break;
  }
  if (timer_update && this->_tac & (1 << 2)) {
    this->_tima++;
    if (this->_tima == 0xFF) {
      this->_tima = this->_tma;
      //      cpu_request_interrupt(IT_TIMER);
    }
  }
}

void pbg_timer::timer_write(uint16_t address, uint8_t value)
{
  if (address == 0xFF04)
    this->_div = 0;
  else if (address == 0xFF05)
    this->_tima = value;
  else if (address == 0xFF06)
    this->_tma = value;
  else if (address == 0xFF07)
    this->_tac = value;
}

uint8_t pbg_timer::timer_read(uint16_t address)
{
  if (address ==  0xFF04)
    return this->_div >> 8;
  else if (address == 0xFF05)
    return this->_tima;
  else if (address == 0xFF06)
    return this->_tma;
  else if (address == 0xFF07)
    return this->_tac;
  else return -1;
}

pbg_timer * pbg_timer::timer_get_context()
{
  return this;
}
