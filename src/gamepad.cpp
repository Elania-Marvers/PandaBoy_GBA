#include "gamepad.hpp"

using namespace pandaboygba;

pbg_gamepad::pbg_gamepad(pbg_context *ctx)
  : _context_ptr(ctx)
{
  std::cout << "🎮 " << RED << "[" << ORANGE << "Running GAMEPAD!" << RED << "]" << DEFAULT << " 🎮" << std::endl;  
}

bool pbg_gamepad::gamepad_button_sel()
{
  return this->button_sel;
}

bool pbg_gamepad::gamepad_dir_sel()
{
  return this->dir_sel;
}

void pbg_gamepad::gamepad_set_sel(uint8_t value)
{
  this->button_sel = value & 0x20;
  this->dir_sel = value & 0x10;
}

gamepad_state *pbg_gamepad::gamepad_get_state()
{
  return &this->controller;
}

uint8_t pbg_gamepad::gamepad_get_output()
{
  uint8_t output = 0xCF;
  if (!this->gamepad_button_sel()) {
    if (this->gamepad_get_state()->start)
      output &= ~(1 << 3);
    if (this->gamepad_get_state()->select)
      output &= ~(1 << 2);
    if (this->gamepad_get_state()->a)
      output &= ~(1 << 0);
    if (this->gamepad_get_state()->b)
      output &= ~(1 << 1);
  }
  if (!this->gamepad_dir_sel()) {
    if (this->gamepad_get_state()->left)
      output &= ~(1 << 1);
    if (this->gamepad_get_state()->right)
      output &= ~(1 << 0);
    if (this->gamepad_get_state()->up)
      output &= ~(1 << 2);
    if (this->gamepad_get_state()->down)
      output &= ~(1 << 3);
  }
  return output;
}
