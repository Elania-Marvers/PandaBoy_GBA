#ifndef		___TIMER_HPP___
#define		___TIMER_HPP___
#include "interrupts.hpp"

using namespace pandaboygba;
namespace pandaboygba
{
  class  pbg_timer
  {
  private:
    uint16_t		_div;
    uint8_t		_tima;
    uint8_t		_tma;
    uint8_t		_tac;
  public:
    pbg_timer();
    void timer_tick();

    void timer_write(uint16_t address, uint8_t value);
    uint8_t timer_read(uint16_t address);
    
    pbg_timer * timer_get_context();
  };
}

#endif
