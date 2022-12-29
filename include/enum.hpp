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
  IN_NONE,
  IN_NOP,
  IN_LD,
  IN_INC,
  IN_DEC,
  IN_RLCA,
  IN_ADD,
  IN_RRCA,
  IN_STOP,
  IN_RLA,
  IN_JR,
  IN_RRA,
  IN_DAA,
  IN_CPL,
  IN_SCF,
  IN_CCF,
  IN_HALT,
  IN_ADC,
  IN_SUB,
  IN_SBC,
  IN_AND,
  IN_XOR,
  IN_OR,
  IN_CP,
  IN_POP,
  IN_JP,
  IN_PUSH,
  IN_RET,
  IN_CB,
  IN_CALL,
  IN_RETI,
  IN_LDH,
  IN_JPHL,
  IN_DI,
  IN_EI,
  IN_RST,
  IN_ERR,
  //CB instructions...
  IN_RLC, 
  IN_RRC,
  IN_RL, 
  IN_RR,
  IN_SLA, 
  IN_SRA,
  IN_SWAP, 
  IN_SRL,
  IN_BIT, 
  IN_RES, 
  IN_SET
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

#endif
