#ifndef		___REGISTER_HPP___
#define		___REGISTER_HPP___
#include "common.hpp"
#pragma once

typedef struct		s_register
{
  uint8_t	a;
  uint8_t	f;
  uint8_t	b;
  uint8_t	c;
  uint8_t	d;
  uint8_t	e;
  uint8_t	h;
  uint8_t	l;
  uint16_t	sp;
  uint16_t	pc;
    
}			t_register;

#endif
