#include "ui.hpp"

using namespace pandaboygba;

pbg_ui::pbg_ui(pbg_context *ctx)
  : _context_ptr(ctx), _ticks(0)
{
  std::cout << "🎮 " << RED << "[" << ORANGE << "Running UI!" << RED << "]" << DEFAULT << " 🎮" << std::endl;  
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
