#ifndef		___GAMEPAD_HPP___
#define		___GAMEPAD_HPP___
#include "common.hpp"
#include "context.hpp"

using namespace pandaboygba;
namespace pandaboygba
{
  class  pbg_context;
  class  pbg_gamepad
  {
  private:
    pbg_context *		_context_ptr;
  public:
    pbg_gamepad(pbg_context *);
  };
}

#endif
