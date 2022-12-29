#ifndef		___PPU_HPP___
#define		___PPU_HPP___

namespace pandaboygba
{
  class pbg_context;
  class  pbg_ppu
  {
  private:
    pbg_context *		_context_ptr;
  public:
    pbg_ppu(pbg_context *);
    void ppu_tick();
  };
}

#endif
