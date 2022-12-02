#include "event_loop.hpp"

void event_loop(gba_emulator *win)
{
  sf::Event		_event;  
  while (win->get_window().pollEvent(_event))
    {
      // to close the window if click on cross or escape
      if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ win->window_stop(); };
    }
}
