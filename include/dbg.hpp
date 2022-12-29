#ifndef		___DBG_HPP___
#define		___DBG_HPP___
#include "common.hpp"
#include "context.hpp"

using namespace pandaboygba;
namespace pandaboygba
{
  class pbg_context;
  class  pbg_dbg
  {
  private:
    pbg_context *		_context_ptr;

  public:
    pbg_dbg(pbg_context *);
    void dbg_update();
    void dbg_print();    
  };
}

#endif
