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
  gba->setRunning();
  gba->set_main_loop(main_loop);
  gba->set_event_loop(event_loop);
  gba->event();
  delete gba;
  return 0;
}

/*********************************************************/
/**	These function is emulator constructor		**/
/*********************************************************/
gba_emulator::gba_emulator()
  : _window(sf::VideoMode(800, 800, 32), "Emulator"), _paused(false), _running(true), _ticks(0), _cart(NULL)
{
  std::cout << "🎮 " << RED << "[" << ORANGE << "Running Emulator!" << RED << "]" << DEFAULT << " 🎮" << std::endl;
  _window.setVerticalSyncEnabled(true);
  _window.setFramerateLimit(60);
}

gba_emulator::~gba_emulator()
{
  /*
  if (this->_cart != NULL)
    {
      delete this->_cart;
      this->_cart = NULL;
    }
  */
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

sf::RenderWindow& gba_emulator::get_window(void)
{
  return this->_window;
}

/*********************************************************/
/**	Those functions are setters from the		**/
/**	gba_emulator class				**/
/*********************************************************/
void	gba_emulator::setPaused(bool state)
{
  this->_paused = state;
}

void	gba_emulator::setRunning(void)
{
  this->_running = _window.isOpen();
}

void	gba_emulator::setTicks(uint64_t state)
{
  this->_ticks = state;
}

void	gba_emulator::loadCart(char *cart)
{
  /*
  if (this->_cart != NULL)
    {
      delete this->_cart;
      this->_cart = NULL;
    }
  this->_cart = new pbg_cart();
  if (this->_cart == NULL)
    return;

  (this->getCart())->cart_load(cart);
  */
}

void gba_emulator::event()
{
  while (this->getRunning()) {
      if (_event_loop != NULL)
	this->_event_loop(this);
      if (_main_loop != NULL)
	this->_main_loop(this);
    this->setRunning();
  }
}

void gba_emulator::set_main_loop(void (*fptr)(gba_emulator *))
{
  this->_main_loop = fptr;
}

void gba_emulator::set_event_loop(void (*fptr)(gba_emulator *))
{
  this->_event_loop = fptr;
}

void gba_emulator::display(void)
{
  this->_window.display();
}

void gba_emulator::window_stop(void)
{
  this->_window.close();
}

void gba_emulator::delay(uint32_t time)
{
  sf::sleep(sf::milliseconds(time));
}
