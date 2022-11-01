#include "cart.hpp"

using namespace pandaboygba;

/*********************************************************/
/**	Those functions are getters from the		**/
/**	pbg_cart class					**/
/*********************************************************/
t_rom_header *	pbg_cart::getRomHeader()	const
{
  return this->_rom_header;
}

char *		pbg_cart::getFileName()	const
{
  return (char *) this->_filename.c_str();
}

uint32_t 	pbg_cart::GetRomSize()	const
{
  return this->_rom_size;
}

uint8_t *	pbg_cart::GetRomData()	const
{
  return this->_rom_data;
}


pbg_cart::pbg_cart()
  :_rom_data(NULL)
{
  std::cout << "🎮 " << RED << "[" << ORANGE << "Loading a cartrige" << RED << "]" << DEFAULT << " 🎮" << std::endl;

  this->_licency_code.insert({{0x00, "None"}, {0x01, "Nintendo R&D1"}, {0x08, "Capcom"}, {0x13, "Electronic Arts"}, {0x18, "Hudson Soft"}, {0x19, "b-ai"}, {0x20, "kss"}, {0x22, "pow"}, {0x24, "PCM Complete"}, {0x25, "san-x"}, {0x28, "Kemco Japan"}, {0x29, "seta"}, {0x30, "Viacom"}, {0x31, "Nintendo"}, {0x32, "Bandai"}, {0x33, "Ocean/Acclaim"}, {0x34, "Konami"}, {0x35, "Hector"}, {0x37, "Taito"}, {0x38, "Hudson"}, {0x39, "Banpresto"}, {0x41, "Ubi Soft"}, {0x42, "Atlus"}, {0x44, "Malibu"}, {0x46, "angel"}, {0x47, "Bullet-Proof"}, {0x49, "irem"}, {0x50, "Absolute"}, {0x51, "Acclaim"}, {0x52, "Activision"}, {0x53, "American sammy"}, {0x54, "Konami"}, {0x55, "Hi tech entertainment"}, {0x56, "LJN"}, {0x57, "Matchbox"}, {0x58, "Mattel"}, {0x59, "Milton Bradley"}, {0x60, "Titus"}, {0x61, "Virgin"}, {0x64, "LucasArts"}, {0x67, "Ocean"}, {0x69, "Electronic Arts"}, {0x70, "Infogrames"}, {0x71, "Interplay"}, {0x72, "Broderbund"}, {0x73, "sculptured"}, {0x75, "sci"}, {0x78, "THQ"}, {0x79, "Accolade"}, {0x80, "misawa"}, {0x83, "lozc"}, {0x86, "Tokuma Shoten Intermedia"}, {0x87, "Tsukuda Original"}, {0x91, "Chunsoft"}, {0x92, "Video system"}, {0x93, "Ocean/Acclaim"}, {0x95, "Varie"}, {0x96, "Yonezawa/s’pal"}, {0x97, "Kaneko"}, {0x99, "Pack in soft"},  {0xA4, "Konami (Yu-Gi-Oh!)"}});

  this->_rom_type.insert({{0x00, "ROM ONLY"}, {0x01, "MBC1"}, {0x02, "MBC1+RAM"}, {0x03,"MBC1+RAM+BATTERY"}, {0x04, "0x04 ???"}, {0x05, "MBC2"},
      {0x06, "MBC2+BATTERY"}, {0x07, "0x07 ???"}, {0x08, "ROM+RAM 1"}, {0x09, "ROM+RAM+BATTERY 1"}, {0x0A, "0x0A ???"}, {0x0B, "MMM01"}, {0x0C, "MMM01+RAM"}, {0x0D, "MMM01+RAM+BATTERY"}, {0x0E, "0x0E ???"}, {0x0F, "MBC3+TIMER+BATTERY"}, {0x10, "MBC3+TIMER+RAM+BATTERY 2"}, {0x11, "MBC3"}, {0x12, "MBC3+RAM 2"}, {0x13, "MBC3+RAM+BATTERY 2"}, {0x14, "0x14 ???"}, {0x15, "0x15 ???"}, {0x16, "0x16 ???"}, {0x17, "0x17 ???"}, {0x18, "0x18 ???"}, {0x19, "MBC5"}, {0x1A, "MBC5+RAM"}, {0x1B, "MBC5+RAM+BATTERY"}, {0x1C, "MBC5+RUMBLE"}, {0x1D, "MBC5+RUMBLE+RAM"}, {0x1E, "MBC5+RUMBLE+RAM+BATTERY"}, {0x1F, "0x1F ???"}, {0x20, "MBC6"}, {0x21, "0x21 ???"}, {0x22, "MBC7+SENSOR+RUMBLE+RAM+BATTERY"}});

  
}

pbg_cart::~pbg_cart()
{
  if (this->_rom_data != NULL)
    delete [] this->_rom_data;
}

/*********************************************************/
/**	Those functions are setters from the		**/
/**	pbg_cart class					**/
/*********************************************************/
void		pbg_cart::setRomHeader(t_rom_header * state)
{
  this->_rom_header = state;
}

void		pbg_cart::setFileName(char *state)
{
  this->_filename = state;
}

void		pbg_cart::setRomSize(uint32_t state)
{
  this->_rom_size = state;
}

void		pbg_cart::setRomData(uint8_t *state)
{
  this->_rom_data = state;
}



/*********************************************************/
/**	These function load a rom cart			**/
/*********************************************************/
bool		pbg_cart::cart_load(const char *cart)
{
  this->_filename = cart;
  std::cout << "🎮 " << RED << "[" << ORANGE << "Loading " << this->_filename.c_str() << RED << "]" << DEFAULT << " 🎮" << std::endl;
  std::FILE* file = std::fopen(cart, "r");

  // Transform to exception !
  if (!file) {
    std::cerr << "❌ Failed to open: " << cart << " [Pour le petit roux SEGFAULT] ❌" << std::endl;
    return false;
  }

  // Transform to c++ readfile
  fseek(file, 0, SEEK_END);
  this->_rom_size = ftell(file);
  rewind(file);
  this->_rom_data = new uint8_t[this->_rom_size];
  fread(this->_rom_data, this->_rom_size, 1, file);
  fclose(file);
  this->_rom_header = (t_rom_header *) (this->_rom_data + 0x100);
  this->_rom_header->title[15] = 0;

  std::cout << "Cartridge Loaded:\n" << std::tab << "Title    : " << this->_rom_header->title << std::endl;

  // Transform to c++ std::cout
  printf("Type     : %2.2X (%s)\n", this->_rom_header->type, this->cart_type_name());
  printf("\t ROM Size : %d KB\n", 32 << this->_rom_header->rom_size);
  printf("\t RAM Size : %2.2X\n", this->_rom_header->ram_size);
  printf("\t LIC Code : %2.2X (%s)\n", this->_rom_header->lic_code, this->cart_lic_name());
  printf("\t ROM Vers : %2.2X\n", this->_rom_header->version);
  return true;
}

const char *	pbg_cart::cart_lic_name()
{
  if (this->_rom_header->new_lic_code <= 0xA4) {
    return this->_licency_code[this->_rom_header->lic_code].c_str();
  }
  return "UNKNOWN";
}

const char *	pbg_cart::cart_type_name()
{
  if (this->_rom_header->type <= 0x22) {
    return this->_rom_type[this->_rom_header->type].c_str();
  }
  return "UNKNOWN";
}
