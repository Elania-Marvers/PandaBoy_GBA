#ifndef		___REGISTER_HPP___
#define		___REGISTER_HPP___

typedef struct		s_register
{
  union
  {
    struct {
      unsigned char	a;
      unsigned char	f;
    };
    unsigned short	af;
  };

  union
  {
    struct {
      unsigned char	b;
      unsigned char	c;
    };
    unsigned short	bc;
  };

  union
  {
    struct {
      unsigned char	d;
      unsigned char	e;
    };
    unsigned short	de;
  };

  union
  {
    struct {
      unsigned char	l;
      unsigned char	h;
    };
    unsigned short	hl;
  };
  
  unsigned short	sp;
  unsigned short	pc;
  
    
}			t_register;

#endif
