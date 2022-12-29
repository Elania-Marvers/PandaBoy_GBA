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

uint8_t	*	pbg_cart::GetRomData()	const
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
  std::ifstream file(cart, std::ios::binary | std::ios::ate);

  // Transform to exception !
  if (!file.is_open()) {
    std::cerr << "❌ Failed to open: " << cart << " [Pour le petit roux SEGFAULT] ❌" << std::endl;
    return false;
  }

  file.seekg(0, file.end);
  this->_rom_size = file.tellg();
  file.clear();
  file.seekg(0);
  this->_rom_data = new uint8_t[this->_rom_size];
  file.read((char *) this->_rom_data, this->_rom_size);
  file.close();
  this->_rom_header = (t_rom_header *) (this->_rom_data + 0x100);
  this->_rom_header->title[15] = 0;

  // CARTRIDGE TITLE
  std::cout << "Cartridge Loaded:\n" << std::tab << "Title" << std::tab << std::tab << ":" << std::tab << this->_rom_header->title << std::endl;
  // Saving Count print Methods
  std::ios init(NULL);
  init.copyfmt(std::cout);
  // CARTRIDGE TYPE
  std::cout << std::tab << "TYPE" << std::tab << std::tab << ":" << std::tab << std::setfill('0') << std::hex << std::setw(2) << std::setprecision(2) << static_cast<unsigned int>(this->_rom_header->type) << " (" << this->cart_type_name() << ")" << std::endl;
  // RESET PRINT METHODS
  std::cout.copyfmt(init);
  // CARTRIDGE ROM SIZE  
  std::cout << std::tab << "ROM SIZE" << std::tab << ":" << std::tab << (32 << this->_rom_header->rom_size) << "KB" << std::endl;
  // CARTRIDGE RAM SIZE
  std::cout << std::tab << "RAM SIZE" << std::tab << ":" << std::tab << std::setfill('0') << std::hex << std::setw(2) << std::setprecision(2) << static_cast<unsigned int>(this->_rom_header->ram_size) << std::endl;
  // CARTRIDGE LIC CODE
  std::cout << std::tab << "LIC CODE" << std::tab << ":" << std::tab << std::setfill('0') << std::hex << std::setw(2) << std::setprecision(2) << static_cast<unsigned int>(this->_rom_header->lic_code) << " (" << this->cart_lic_name() << ")" << std::endl;
  
  // CARTRIDGE ROM VERSION
  std::cout << std::tab << "ROM VERSION" << std::tab << ":" << std::tab << std::setfill('0') << std::hex << std::setw(2) << std::setprecision(2) << static_cast<unsigned int>(this->_rom_header->version) << std::endl;
  // RESET PRINT METHODS
  std::cout.copyfmt(init);

  this->cart_setup_banking();
  
  uint16_t x = 0;
  for (uint16_t i = 0x0134; i <= 0x014C; i++)
    {
      x = x - this->_rom_data[i] - 1;
    }

  // CARTRIDGE CHECKSUM
  std::cout << std::tab << "CHECKSUM" << std::tab << ":" << std::tab << std::setfill('0') << std::hex << std::setw(2) << std::setprecision(2) << static_cast<unsigned int>(this->_rom_header->checksum) << " (" << ((x & 0xFF) ? "PASSED" : "FAILED") << ")" << std::endl;

  if (this->battery) {
    this->cart_battery_load();
  }

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

uint8_t		pbg_cart::cart_read(uint16_t	address)	const
{
  if (!this->cart_mbc1() || address < 0x4000) {
    return this->_rom_data[address];
  }

  if ((address & 0xE000) == 0xA000) {
    if (!this->_ram_enabled) {
      return 0xFF;
    }
    if (!this->_ram_bank) {
      return 0xFF;
    }
    return this->_ram_bank[address - 0xA000];
  }
  return this->_rom_bank_x[address - 0x4000];
}

void	pbg_cart::cart_write(uint16_t	address, uint8_t	value)
{
  if (!this->cart_mbc1())
    return;
  if (address < 0x2000)
    this->_ram_enabled = ((value & 0xF) == 0xA);
  if ((address & 0xE000) == 0x2000)
    {
      //rom bank number
      if (value == 0)
	value = 1;
      value &= 0b11111;
      this->_rom_bank_value = value;
      this->_rom_bank_x = this->_rom_data + (0x4000 * this->_rom_bank_value);
    }
  if ((address & 0xE000) == 0x4000) {
    //ram bank number
    this->_ram_bank_value = value & 0b11;
    if (this->_ram_banking) {
      if (this->cart_need_save())
	this->cart_battery_save();
      this->_ram_bank = this->_ram_banks[this->_ram_bank_value];
    }
  }
  if ((address & 0xE000) == 0x6000) {
    //banking mode select
    this->_banking_mode = value & 1;
    this->_ram_banking = this->_banking_mode;
    if (this->_ram_banking) {
      if (this->cart_need_save())
	this->cart_battery_save();
      this->_ram_bank = this->_ram_banks[this->_ram_bank_value];
    }
  }
  if ((address & 0xE000) == 0xA000) {
    if (!this->_ram_enabled)
      return;
    if (!this->_ram_bank) 
      return;
    this->_ram_bank[address - 0xA000] = value;
    if (this->_battery)
      this->_need_save = true;
  }
}

const bool pbg_cart::cart_need_save() {
  return this->need_save;
}

const bool pbg_cart::cart_mbc1() {
  return BETWEEN(this->_rom_header->type, 1, 3);
}

const bool pbg_cart::cart_battery() {
  return this->_rom_header->type == 3;
}

void pbg_cart::cart_setup_banking() {
  for (int i = 0; i < 16; i++)
    {
      this->ram_banks[i] = 0;
      if ((this->_rom_header->ram_size == 2 && i == 0) ||
	  (this->_rom_header->ram_size == 3 && i < 4) || 
	  (this->_rom_header->ram_size == 4 && i < 16) || 
	  (this->_rom_header->ram_size == 5 && i < 8))
	{
	  this->ram_banks[i] = new uint8_t[0x2000];
	  memset(this->ram_banks[i], 0, 0x2000);
        }
    }
  this->ram_bank = this->ram_banks[0];
  this->rom_bank_x = this->rom_data + 0x4000; //rom bank 1
}

void pbg_cart::cart_battery_load() {
  if (!this->ram_bank) {
    return;
  }
  std::string fn = this->filename + ".battery";
  std::ifstream file(fn, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "❌ Failed to open: " << cart << " [Pour le petit roux SEGFAULT] ❌" << std::endl;
    return;
  }
  file.read(reinterpret_cast<char*>(this->ram_bank), 0x2000);
  file.close();
}



void pbg_cart::cart_battery_save() {
  if (!this->ram_bank) {
    return;
  }
  std::string fn = this->filename + ".battery";
  std::ofstream fp(fn, std::ios::binary);
  if (!fp.is_open()) {
    std::cerr << "❌ Failed to open: " << cart << " [Pour le petit roux SEGFAULT] ❌" << std::endl;
    return;
  }
  fp.write(reinterpret_cast<char*>(this->ram_bank), 0x2000);
  fp.close();
}
