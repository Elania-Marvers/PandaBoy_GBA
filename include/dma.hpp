#ifndef		___DMA_HPP___
#define		___DMA_HPP___
#include "common.hpp"
#include "context.hpp"

using namespace pandaboygba;
namespace pandaboygba
{
  class pbg_context;
  class  pbg_dma
  {
  private:
    pbg_context *		_context_ptr;
  public:
    pbg_dma(pbg_context *);
  };
}

#endif
