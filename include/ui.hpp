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
    pbg_ui(pbg_context *);
  };
}

#endif
