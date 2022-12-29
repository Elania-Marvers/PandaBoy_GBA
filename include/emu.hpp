#ifndef		___EMU_HPP___
#define		___EMU_HPP___
#include <SFML/Graphics.hpp>
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
    sf::RenderWindow	_window;	// This represent the window of sfml
    bool		_paused;	// This represent if the emulator is un pause
    bool		_running;	// This represent if the emulator is running
    uint64_t		_ticks;		// This represent the emulator ticks
    pbg_context *	_context;	// This represent the context
    void (*_main_loop)(gba_emulator *);	// This is the main event loop
    void (*_event_loop)(gba_emulator *);// This is the event input loop
    
    
  public:
    bool		getPaused()	const;
    bool		getRunning()	const;
    uint64_t		getTicks()	const;
    pbg_context&	getContext();
    sf::RenderWindow&	get_window(void);
    
    void	setPaused(bool);
    void	setRunning(void);
    void	setTicks(uint64_t);
    void	loadCart(char *);

    void	event();
    void	delay(uint32_t);
    void	set_main_loop(void (*fptr)(gba_emulator *));
    void	set_event_loop(void (*fptr)(gba_emulator *));
    void	display(void);
    void	window_stop(void);
    
		gba_emulator();
		~gba_emulator();

  };
};

int pbg_emu_run (int		argc,
		 const	char **	argv);

void main_loop(gba_emulator *win);
void event_loop(gba_emulator *win);
#endif
