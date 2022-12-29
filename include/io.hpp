#ifndef		___IO_HPP___
#define		___IO_HPP___
#include "common.hpp"
#include "context.hpp"

using namespace pandaboygba;
namespace pandaboygba
{
  class pbg_context;
  class  pbg_io
  {
  private:
    pbg_context *		_context_ptr;
  public:
    pbg_io(pbg_context *);

    uint8_t io_read(uint16_t address);
    void io_write(uint16_t address, uint8_t value);
    
  };
}

#endif
