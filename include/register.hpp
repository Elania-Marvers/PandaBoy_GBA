#ifndef		___REGISTER_HPP___
#define		___REGISTER_HPP___
#include "common.hpp"

typedef struct		s_register
{
  union
  {
    struct {
      uint8_t	a;
      uint8_t	f;
    };
    uint16_t	af;
  };

  union
  {
    struct {
      uint8_t	b;
      uint8_t	c;
    };
    uint16_t	bc;
  };

  union
  {
    struct {
      uint8_t	d;
      uint8_t	e;
    };
    uint16_t	de;
  };

  union
  {
    struct {
      uint8_t	l;
      uint8_t	h;
    };
    uint16_t	hl;
  };
  
  uint16_t	sp;
  uint16_t	pc;
    
}			t_register;

#endif
