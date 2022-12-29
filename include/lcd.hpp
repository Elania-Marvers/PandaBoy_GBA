#ifndef		___LCD_HPP___
#define		___LCD_HPP___
#include "common.hpp"
#include "context.hpp"

using namespace pandaboygba;
namespace pandaboygba
{
  class pbg_context;
  class  pbg_lcd
  {
  private:
    pbg_context *		_context_ptr;
  public:
    pbg_lcd(pbg_context *);
  };
}

#endif
