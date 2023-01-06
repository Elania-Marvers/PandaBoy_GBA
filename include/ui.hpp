#ifndef		___UI_HPP___
#define		___UI_HPP___
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "common.hpp"
#include "context.hpp"

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 580;

using namespace pandaboygba;
namespace pandaboygba
{
  class  pbg_ui
  {
  private:
    pbg_context *		_context_ptr;
    sf::RenderTexture _windowRenderTexture;
    sf::Texture _windowTexture;
    sf::Image _windowScreen;
    sf::RenderWindow _debugWindow;
    sf::RenderTexture _debugRenderTexture;
    sf::Texture _debugTexture;
    sf::Image _debugScreen;

  public:
    bool active = false;
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
    void ui_on_key(bool down, sf::Keyboard::Key key_code);
    void ui_on_joystick(bool down, sf::Joystick::Axis axis, unsigned int joystick);
    void ui_on_joystick_btn(sf::Joystick::Axis axis, unsigned int joystick);
  };
}

#endif
