#ifndef		___EMU_HPP___
#define		___EMU_HPP___
#include <SFML/Graphics.hpp>
#include <pthread.h>
#include "common.hpp"
#include "context.hpp"
#include "cart.hpp"

using namespace pandaboygba;
namespace pandaboygba
{
  class pbg_context;
  class gba_emulator
  {
  private:
    bool		_paused;	// This represent if the emulator is un pause
    bool		_running;	// This represent if the emulator is running
    void (*_main_loop)(gba_emulator *);	// This is the main event loop
    void (*_event_loop)(gba_emulator *);// This is the event input loop
        
  public:
    pbg_context *	_context;	// This represent the context
    bool		_die;		// This is the die xD
    bool		getPaused()	const;
    bool		getRunning()	const;
    pbg_context&	getContext();
    void	setPaused(bool);
    void	setRunning(void);
    void	loadCart(char *);
    void	event();
    void	set_main_loop(void (*fptr)(gba_emulator *));
    void	set_event_loop(void (*fptr)(gba_emulator *));
    void	display(void);
    void	emu_cycles(int);
    gba_emulator();
    ~gba_emulator();
  };
};

int pbg_emu_run (int		argc,
		 const	char **	argv);
void main_loop(gba_emulator *win);
void event_loop(gba_emulator *win);
#endif
