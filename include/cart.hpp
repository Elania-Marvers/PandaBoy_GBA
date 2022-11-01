#ifndef		___CART_HPP___
#define		___CART_HPP___
#include "common.hpp"
#include <cstring>
#include <map>

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
    std::map<int, std::string>		_licency_code;
    std::map<int, std::string>	        _rom_type;
    
  public:
    t_rom_header *	getRomHeader()	const;
    char *		getFileName()	const;
    uint32_t 		GetRomSize()	const;
    uint8_t *		GetRomData()	const;

    void		setRomHeader(t_rom_header *);
    void		setFileName(char *);
    void		setRomSize(uint32_t);
    void		setRomData(uint8_t *);
    
			pbg_cart();
			~pbg_cart();
    
    bool		cart_load(const char *);
    const char *	cart_lic_name();
    const char *        cart_type_name();
  };
}


#endif
