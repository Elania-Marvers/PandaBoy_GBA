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
    bool active;
    uint8_t byte;
    uint8_t value;
    uint8_t start_delay;
    pbg_context *		_context_ptr;

  public:
    pbg_dma(pbg_context *);
    void dma_start(uint8_t start);
    void dma_tick();
    bool dma_transferring();
    
  };
}

#endif
