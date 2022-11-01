#include "emu.hpp"

using namespace pandaboygba;

/*********************************************************/
/**	These function run the emulator			**/
/*********************************************************/
int pbg_emu_run (int		argc,
		 const	char **	argv)
{
  if (argc < 2)
    {
      std::cout << "🎮 Usage: " << argv[0] << " <rom_file>" << std::endl;
      return -1;
    }
  gba_emulator *gba = new gba_emulator();
  gba->loadCart((char *) argv[1]);
  delete gba;
  return 0;
}

/*********************************************************/
/**	These function is emulator constructor		**/
/*********************************************************/
gba_emulator::gba_emulator()
  : _paused(false), _running(true), _ticks(0), _cart(NULL)
{
  std::cout << "🎮 " << RED << "[" << ORANGE << "Running Emulator!" << RED << "]" << DEFAULT << " 🎮" << std::endl;
}

gba_emulator::~gba_emulator()
{
  if (this->_cart != NULL)
    {
      delete this->_cart;
      this->_cart = NULL;
    }
}

/*********************************************************/
/**	Those functions are getters from the		**/
/**	gba_emulator class				**/
/*********************************************************/
bool	gba_emulator::getPaused()	const
{
  return this->_paused;
}

bool	gba_emulator::getRunning()	const
{
  return this->_running;
}

uint64_t	gba_emulator::getTicks()	const
{
  return this->_ticks;
}

pbg_cart *	gba_emulator::getCart()	const
{
  return this->_cart;
}

/*********************************************************/
/**	Those functions are setters from the		**/
/**	gba_emulator class				**/
/*********************************************************/
void	gba_emulator::setPaused(bool state)
{
  this->_paused = state;
}

void	gba_emulator::setRunning(bool state)
{
  this->_running = state;
}

void	gba_emulator::setTicks(uint64_t state)
{
  this->_ticks = state;
}

void	gba_emulator::loadCart(char *cart)
{
  if (this->_cart != NULL)
    {
      delete this->_cart;
      this->_cart = NULL;
    }
  this->_cart = new pbg_cart();
  if (this->_cart == NULL)
    return;

  (this->getCart())->cart_load(cart);
}
