#ifndef		___RAM_HPP___
#define		___RAM_HPP___
#include "common.hpp"
#include "context.hpp"

using namespace pandaboygba;
namespace pandaboygba
{
  class pbg_context;

  class  pbg_ram
  {
  private:
    pbg_context	*	_context_ptr;
  public:
    pbg_ram(pbg_context	*);
  };
}

#endif
