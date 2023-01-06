#ifndef		___CART_HPP___
#define		___CART_HPP___
#include "common.hpp"
#include "enum.hpp"
#include "context.hpp"
#include <cstring>
#include <map>
#include <fstream>
#include <iomanip>

using namespace pandaboygba; 
namespace pandaboygba
{
  class pbg_context;  
  class  pbg_cart
  {
  private:
    t_rom_header *			_rom_header;
    std::string				_filename;
    uint32_t				_rom_size;
    uint8_t *				_rom_data;
    bool				_ram_enabled; // ][
    bool				_ram_banking;
    uint8_t *				_rom_bank_x;
    uint8_t				_banking_mode;
    uint8_t				_rom_bank_value;
    uint8_t				_ram_bank_value;
    uint8_t *				_ram_bank;		//current selected ram bank
    uint8_t *				_ram_banks[16];		//all ram banks
    bool				_battery;		//has battery
    bool				_need_save;		//should save battery backup.
    std::map<int, std::string>		_licency_code;
    std::map<int, std::string>	        _rom_type;
    pbg_context *		_context_ptr;
  private:
    const char *	cart_lic_name();
    const char *        cart_type_name();
    bool		cart_mbc1() const;
    const bool		cart_battery();
    
  public:
    t_rom_header *	getRomHeader()	const;
    char *		getFileName()	const;
    uint32_t 		GetRomSize()	const;
    uint8_t *		GetRomData()	const;
    const bool		cart_need_save();
    void		setRomHeader(t_rom_header *);
    void		setFileName(char *);
    void		setRomSize(uint32_t);
    void		setRomData(uint8_t *);
    pbg_cart(pbg_context *);
    ~pbg_cart();
    bool		cart_load(const char *);
    uint8_t		cart_read(uint16_t	address)	const;
    void		cart_write(uint16_t	address, uint8_t	value);
    void		cart_battery_load();
    void		cart_battery_save();
    void		cart_setup_banking();
    
  };
}

#endif
