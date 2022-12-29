#ifndef		___CART_HPP___
#define		___CART_HPP___
#include "common.hpp"
#include <cstring>
#include <map>
#include <fstream>
#include <iomanip>

#pragma once
typedef struct		s_rom_header{
  uint8_t		entry[4];
  uint8_t		logo[0x30]; // 48bits !
  char			title[16];
  uint16_t		new_lic_code;
  uint8_t		sgb_flag;
  uint8_t		type;
  uint8_t		rom_size;
  uint8_t		ram_size;
  uint8_t		dest_code;
  uint8_t		lic_code;
  uint8_t		version;
  uint8_t		checksum;
  uint16_t		global_checksum;
}			t_rom_header;

namespace pandaboygba
{
  
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
    
    pbg_cart();
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
