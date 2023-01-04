#ifndef		___ENUM_HPP___
#define		___ENUM_HPP___

  typedef enum {
    MODE_HBLANK,
    MODE_VBLANK,
    MODE_OAM,
    MODE_XFER
  } lcd_mode;

  typedef enum {
    SS_HBLANK = (1 << 3),
    SS_VBLANK = (1 << 4),
    SS_OAM = (1 << 5),
    SS_LYC = (1 << 6),
  } stat_src;

typedef enum {
  AM_IMP,
  AM_R_D16,
  AM_R_R,
  AM_MR_R,
  AM_R,
  AM_R_D8,
  AM_R_MR,
  AM_R_HLI,
  AM_R_HLD,
  AM_HLI_R,
  AM_HLD_R,
  AM_R_A8,
  AM_A8_R,
  AM_HL_SPR,
  AM_D16,
  AM_D8,
  AM_D16_R,
  AM_MR_D8,
  AM_MR,
  AM_A16_R,
  AM_R_A16
} addr_mode;

typedef enum {
  RT_NONE,
  RT_A,
  RT_F,
  RT_B,
  RT_C,
  RT_D,
  RT_E,
  RT_H,
  RT_L,
  RT_AF,
  RT_BC,
  RT_DE,
  RT_HL,
  RT_SP,
  RT_PC
} reg_type;

typedef enum {
  IN_NONE, //0
  IN_NOP,  //1
  IN_LD,   //2
  IN_INC,  //3
  IN_DEC,  //4
  IN_RLCA, //5
  IN_ADD,  //6
  IN_RRCA, //7
  IN_STOP, //8
  IN_RLA,  //9
  IN_JR,   //10
  IN_RRA,  //11
  IN_DAA,  //12
  IN_CPL,  //13
  IN_SCF,  //14
  IN_CCF,  //15
  IN_HALT, //16
  IN_ADC,  //17
  IN_SUB,  //18
  IN_SBC,  //19
  IN_AND,  //20
  IN_XOR,  //21
  IN_OR,   //22
  IN_CP,   //23
  IN_POP,  //24
  IN_JP,   //25
  IN_PUSH, //26
  IN_RET,  //27
  IN_CB,   //28
  IN_CALL, //29
  IN_RETI, //30
  IN_LDH,  //31
  IN_JPHL, //32
  IN_DI,   //33
  IN_EI,   //34
  IN_RST,  //35
  IN_ERR,  //36
  //CB instructions...
  IN_RLC,  //37
  IN_RRC,  //38
  IN_RL,   //39
  IN_RR,   //40
  IN_SLA,  //41
  IN_SRA,  //42
  IN_SWAP, //43
  IN_SRL,  //44
  IN_BIT,  //45
  IN_RES,  //46
  IN_SET   //47
} in_type;

typedef enum {
  CT_NONE, CT_NZ, CT_Z, CT_NC, CT_C
} cond_type;

  typedef enum {
    IT_VBLANK = 1,
    IT_LCD_STAT = 2,
    IT_TIMER = 4,
    IT_SERIAL = 8,
    IT_JOYPAD = 16
  } interrupt_type;

  typedef enum {
    FS_TILE,
    FS_DATA0,
    FS_DATA1,
    FS_IDLE,
    FS_PUSH
} fetch_state;

typedef struct {
    in_type		_type;
    addr_mode		_mode;
    reg_type		_reg_1;
    reg_type		_reg_2;
    cond_type		_cond;
    uint8_t 		_param;
}		instruction_t;




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



#endif
