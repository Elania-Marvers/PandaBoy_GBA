#include "cart.hpp"

using namespace pandaboygba;

/*********************************************************/
/**	Those functions are getters from the		**/
/**	pbg_cart class					**/
/*********************************************************/
t_rom_header	pbg_cart::getRomHeader()	const
{
  return this->rom_header;
}

char *		pbg_cart::getFileName()	const
{
  return this->filename;
}

uint32_t 	pbg_cart::GetRomSize()	const
{
  return this->rom_size;
}

uint8_t *	pbg_cart::GetRomData()	const
{
  return this->rom_data;
}



/*********************************************************/
/**	Those functions are setters from the		**/
/**	pbg_cart class					**/
/*********************************************************/
void		pbg_cart::setRomHeader(t_rom_header state)
{
  this->rom_header = state;
}

void		pbg_cart::setFileName(char *state)
{
  this->filename = state;
}

void		pbg_cart::setRomSize(uint32_t state)
{
  this->rom_size = state;
}

void		pbg_cart::setRomData(uint8_t *state)
{
  this->rom_data = state;
}



/*********************************************************/
/**	These function load a rom cart			**/
/*********************************************************/
bool		pbg_cart::cart_load(const char *cart)
{
  snprintf(this->filename, sizeof(this->filename), "%s", cart);
  
}
