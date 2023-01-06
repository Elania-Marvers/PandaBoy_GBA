#include "event_loop.hpp"

void event_loop(gba_emulator *win)
{
  sf::Event		_event;  
  while (win->getContext()._ui_ptr->get_window().pollEvent(_event))
    {
      // to close the window if click on cross or escape
      if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ win->getContext()._ui_ptr->window_stop(); win->_die = true; };
    
      if (_event.type == sf::Event::KeyPressed) 
        win->getContext()._ui_ptr->ui_on_key(true, _event.key.code);

      if (_event.type == sf::Event::KeyReleased) 
        win->getContext()._ui_ptr->ui_on_key(false, _event.key.code);

      if (_event.type == sf::Event::JoystickMoved)
	win->getContext()._ui_ptr->ui_on_joystick(true, _event.joystickMove.axis, _event.joystickMove.joystickId);

      if (_event.type == sf::Event::JoystickButtonPressed || _event.type == sf::Event::JoystickButtonReleased)
	win->getContext()._ui_ptr->ui_on_joystick_btn(_event.joystickMove.axis, _event.joystickMove.joystickId);

    }
}
