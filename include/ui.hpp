#ifndef		___UI_HPP___
#define		___UI_HPP___
#include "common.hpp"
#include "context.hpp"

using namespace pandaboygba;
namespace pandaboygba
{
  class  pbg_ui
  {
  private:
    pbg_context *		_context_ptr;
  public:
    uint64_t		_ticks;		// This represent the emulator ticks
    sf::RenderWindow	_window;	// This represent the window of sfml

    
    pbg_ui(pbg_context *);
    uint64_t		getTicks()	const;
    void	setTicks(uint64_t);
    void	delay(uint32_t);
    sf::RenderWindow&	get_window(void);
    void	window_stop(void);


    void ui_update();
    void update_dbg_window();
    void display_tile(sf::Image *surface, uint16_t startLocation, uint16_t tileNum, int x, int y);
    void ui_on_key(bool down, uint32_t key_code);


  };
}

#endif
