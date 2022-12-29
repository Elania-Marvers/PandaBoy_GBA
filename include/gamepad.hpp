#ifndef		___GAMEPAD_HPP___
#define		___GAMEPAD_HPP___
#include "common.hpp"
#include "context.hpp"

typedef struct {
    bool start;
    bool select;
    bool a;
    bool b;
    bool up;
    bool down;
    bool left;
    bool right;
} gamepad_state;

using namespace pandaboygba;
namespace pandaboygba
{
  class  pbg_context;
  class  pbg_gamepad
  {
  private:
    pbg_context *		_context_ptr;
    gamepad_state controller;
    bool button_sel;
    bool dir_sel;
    
  public:
    pbg_gamepad(pbg_context *);
    bool gamepad_button_sel();
    bool gamepad_dir_sel();
    void gamepad_set_sel(uint8_t value);

    gamepad_state *gamepad_get_state();
    uint8_t gamepad_get_output();

  };
}

#endif
