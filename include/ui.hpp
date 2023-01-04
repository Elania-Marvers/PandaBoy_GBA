#ifndef		___UI_HPP___
#define		___UI_HPP___
#include <SFML/Graphics.hpp>
#include "common.hpp"
#include "context.hpp"

static const int SCREEN_WIDTH = 1024;
static const int SCREEN_HEIGHT = 768;


using namespace pandaboygba;
namespace pandaboygba
{
  class  pbg_ui
  {
  private:
    pbg_context *		_context_ptr;
  public:
    bool active = false;
    uint64_t		_ticks;		// This represent the emulator ticks
    sf::RenderWindow	_window;	// This represent the window of sfml
    sf::RenderTexture _windowRenderTexture;
    sf::Texture _windowTexture;
    sf::Image _windowScreen;

    sf::RenderWindow _debugWindow;
    sf::RenderTexture _debugRenderTexture;
    sf::Texture _debugTexture;
    sf::Image _debugScreen;
    
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
