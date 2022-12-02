#ifndef		___CPU_HPP___
#define		___CPU_HPP___
#include "common.hpp"
#include <stdbool.h>

namespace pandaboygba
{
  class  pbg_cpu
  {
  private:
  public:
    pbg_cpu();
    bool cpu_step();
  };
}

#endif
