#include "ui.hpp"

using namespace pandaboygba;
static unsigned long tile_colors[4] = {0xFFFFFFFF, 0xFFAAAAAA, 0xFF555555, 0xFF000000};
static int scale = 4;

pbg_ui::pbg_ui(pbg_context *ctx)
  : _context_ptr(ctx), _ticks(0), _window(sf::VideoMode(800, 800, 32), "Emulator")
{
  std::cout << "🎮 " << RED << "[" << ORANGE << "Running UI!" << RED << "]" << DEFAULT << " 🎮" << std::endl;
  _window.setVerticalSyncEnabled(true);
  _window.setFramerateLimit(60);
}

sf::RenderWindow& pbg_ui::get_window(void)
{
  return this->_window;
}

void pbg_ui::window_stop(void)
{
  this->_window.close();
}

void pbg_ui::delay(uint32_t time)
{
  sf::sleep(sf::milliseconds(time));
}


void	pbg_ui::setTicks(uint64_t state)
{
  this->_ticks = state;
}

uint64_t	pbg_ui::getTicks()	const
{
  return this->_ticks;
}

void pbg_ui::ui_update()
{
}

void pbg_ui::update_dbg_window()
{
}

void pbg_ui::display_tile(sf::Image *surface, uint16_t startLocation, uint16_t tileNum, int x, int y)
{
}

void pbg_ui::ui_on_key(bool down, uint32_t key_code)
{
}
