#ifndef		___UI_HPP___
#define		___UI_HPP___
#include "common.hpp"
#include "context.hpp"

using namespace pandaboygba;
namespace pandaboygba
{
  class  pbg_ui
  {
  private:
    pbg_context *		_context_ptr;
  public:
    uint64_t		_ticks;		// This represent the emulator ticks

    
    pbg_ui(pbg_context *);
    uint64_t		getTicks()	const;
    void	setTicks(uint64_t);
    void	delay(uint32_t);

  };
}

#endif
