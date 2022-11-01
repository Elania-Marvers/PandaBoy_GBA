#ifndef		___EMU_HPP___
#define		___EMU_HPP___
#include "common.hpp"
#include "cart.hpp"

using namespace pandaboygba;
namespace pandaboygba
{
  class gba_emulator
  {
  private:
    bool		_paused;	// This represent if the emulator is un pause
    bool		_running;	// This represent if the emulator is running
    uint64_t		_ticks;		// This represent the emulator ticks
    pbg_cart *		_cart;		// This represent the cartrige
    
  public:
    bool	getPaused()	const;
    bool	getRunning()	const;
    uint64_t	getTicks()	const;
    pbg_cart *	getCart()	const;
    
    void	setPaused(bool);
    void	setRunning(bool);
    void	setTicks(uint64_t);
    void	loadCart(char *);

		gba_emulator();
		~gba_emulator();

  };
};

int pbg_emu_run (int		argc,
		 const	char **	argv);

#endif
