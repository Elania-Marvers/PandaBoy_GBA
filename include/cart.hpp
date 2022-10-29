#ifndef		___CART_HPP___
#define		___CART_HPP___
#include "common.hpp"

#pragma once

typedef struct		s_rom_header{
  uint8_t		entry[4];
  uint8_t		logo[0x30];
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
    t_rom_header	rom_header;
    char		*filename;
    uint32_t		rom_size;
    uint8_t *		rom_data;
   
  public:
    t_rom_header	getRomHeader()	const;
    char *		getFileName()	const;
    uint32_t 		GetRomSize()	const;
    uint8_t *		GetRomData()	const;

    void		setRomHeader(t_rom_header);
    void		setFileName(char *);
    void		setRomSize(uint32_t);
    void		setRomData(uint8_t *);
    
   
    bool		cart_load(const char *);
  };
}


#endif
