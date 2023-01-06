#include "emu.hpp"
#include <unistd.h>

using namespace pandaboygba;

static gba_emulator *gba_ptr;

void *cpu_run (void *p)
{
  printf("Thread CPU RUN[%d]\n", gba_ptr->_context->_cpu_ptr->_halted);
  while(gba_ptr->getRunning())
    {
      if (gba_ptr->getPaused())
	{
	  gba_ptr->getContext()._ui_ptr->delay(10);
	  continue;
	}
      {
	if (!gba_ptr->getContext()._cpu_ptr->cpu_step())
	  {
	    printf("CPU Stopped\n");
	    return 0;
	  }
      }
    }
  printf("Thread CPU STOP\n");
  return 0;
}

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
  pthread_t t1;
  uint32_t prev_frame = 0;
  gba_emulator *gba = new gba_emulator();
  gba_ptr = gba;
  gba->loadCart((char *) argv[1]);
  gba->setRunning();
  gba->set_main_loop(main_loop);
  gba->set_event_loop(event_loop);
  if (pthread_create(&t1, NULL, cpu_run, NULL))
    {
      fprintf(stderr, "FAILED TO START MAIN CPU THREAD!\n");
      return -1;
    }
  while(gba->getRunning())
    {
      usleep(1000);
      gba->event();
      if (prev_frame != ppu_get_context()->current_frame) 
      	gba->getContext()._ui_ptr->ui_update();
      prev_frame = ppu_get_context()->current_frame;
    }
  delete gba;
  return 0;
}

/*********************************************************/
/**	These function is emulator constructor		**/
/*********************************************************/
gba_emulator::gba_emulator()
  : _paused(false), _running(true)
{
  this->_context = new pbg_context(this);
  std::cout << "🎮 " << RED << "[" << ORANGE << "Running Emulator!" << RED << "]" << DEFAULT << " 🎮" << std::endl;
}

gba_emulator::~gba_emulator()
{
  delete this->_context;
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

pbg_context& 	gba_emulator::getContext()      
{
  return *(this->_context);
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
  this->_running = this->_context->_ui_ptr->_window.isOpen();
}

void	gba_emulator::loadCart(char *cart)
{
  this->getContext()._cart_ptr->cart_load(cart);
}

void gba_emulator::event()
{
  if (_event_loop != NULL)
    this->_event_loop(this);
  if (_main_loop != NULL)
    this->_main_loop(this);
  this->setRunning();
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
  this->_context->_ui_ptr->_window.display();
}

void gba_emulator::emu_cycles(int cpu_cycles)
{
  for (int i = 0; i < cpu_cycles; i++)
    {
      for (int n = 0; n < 4; n++)
	{
	  this->_context->_ui_ptr->_ticks++;
	  this->_context->_timer_ptr->timer_tick();
	  this->_context->_ppu_ptr->ppu_tick();
        }
      this->_context->_dma_ptr->dma_tick();
    }
}
