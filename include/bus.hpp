#ifndef		___BUS_HPP___
#define		___BUS_HPP___
#include "common.hpp"
#include "context.hpp"

namespace pandaboygba
{
  class  pbg_bus
  {
  private:
    pbg_context *		_context_ptr;
  public:
    uint8_t	bus_read	(uint16_t	address);
    void	bus_write	(uint16_t	address,
				 uint8_t	value);
    uint8_t	bus_read16	(uint16_t	address);
    void	bus_write16	(uint16_t	address,
				 uint16_t	value);    
  };
}

#endif
