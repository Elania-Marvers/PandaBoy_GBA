#include "cpu.hpp"

using namespace pandaboygba;

uint16_t pbg_cpu::reverse(uint16_t n) {
  return ((n & 0xFF00) >> 8) | ((n & 0x00FF) << 8);
}

t_register *pbg_cpu::cpu_get_regs()
{
  return &(this->_regs);
}

uint16_t pbg_cpu::cpu_read_reg(reg_type rt) {
  switch(rt) {
  case RT_A: return this->_regs.a;
  case RT_F: return this->_regs.f;
  case RT_B: return this->_regs.b;
  case RT_C: return this->_regs.c;
  case RT_D: return this->_regs.d;
  case RT_E: return this->_regs.e;
  case RT_H: return this->_regs.h;
  case RT_L: return this->_regs.l;
  case RT_AF: return this->reverse(*((uint16_t *)&this->_regs.a));
  case RT_BC: return this->reverse(*((uint16_t *)&this->_regs.b));
  case RT_DE: return this->reverse(*((uint16_t *)&this->_regs.d));
  case RT_HL: return this->reverse(*((uint16_t *)&this->_regs.h));
  case RT_PC: return this->_regs.pc;
  case RT_SP: return this->_regs.sp;
  default: return 0;
  }
}

void pbg_cpu::cpu_set_reg(reg_type rt, uint16_t val) {
  //      if (this->_context_ptr->_ui_ptr->_ticks > 985044 && 
  //     this->_context_ptr->_ui_ptr->_ticks < 986184
  //     )
  //  printf("rt[%04X] val[%04X][%04X]\n", rt, val, val & 0xFF);
  switch(rt) {
  case RT_A: 
    /*
      if (this->_context_ptr->_ui_ptr->_ticks > 986000 && 
      this->_context_ptr->_ui_ptr->_ticks < 986184
      ){
      printf("_fetched_data = %04X\n", this->_fetched_data);
      printf("_reg a = %04X\n", this->_regs.a);
      printf("val = %04X\n", val);
      }
    */
    this->_regs.a = val & 0xFF; 
  
    /*
      if (this->_context_ptr->_ui_ptr->_ticks > 986000 && 
      this->_context_ptr->_ui_ptr->_ticks < 986184
      ){
      printf("_fetched_data = %04X\n", this->_fetched_data);
      printf("_reg a = %04X\n", this->_regs.a);
      printf("val = %04X\n", val);
      }
    */
    break;
  case RT_F: this->_regs.f = val & 0xFF; break;
  case RT_B: this->_regs.b = val & 0xFF; break;
  case RT_C: {
    this->_regs.c = val & 0xFF;
  } break;
  case RT_D: this->_regs.d = val & 0xFF; break;
  case RT_E: this->_regs.e = val & 0xFF; break;
  case RT_H: this->_regs.h = val & 0xFF; break;
  case RT_L: this->_regs.l = val & 0xFF; break;
  case RT_AF: {
    *((uint16_t *)&this->_regs.a) = this->reverse(val); 
    break;
  }
  case RT_BC: {
    *((uint16_t *)&this->_regs.b) = this->reverse(val); 
    break;
  }
  case RT_DE: {
    *((uint16_t *)&this->_regs.d) = this->reverse(val); 
    break;
  }
  case RT_HL: {
    *((uint16_t *)&this->_regs.h) = this->reverse(val); 
    break;
  }
  case RT_PC: this->_regs.pc = val; break;
  case RT_SP: this->_regs.sp = val; break;
  case RT_NONE: break;
  }
}


uint8_t pbg_cpu::cpu_read_reg8(reg_type rt) {
  switch(rt) {
  case RT_A: return this->_regs.a;
  case RT_F: return this->_regs.f;
  case RT_B: return this->_regs.b;
  case RT_C: return this->_regs.c;
  case RT_D: return this->_regs.d;
  case RT_E: return this->_regs.e;
  case RT_H: return this->_regs.h;
  case RT_L: return this->_regs.l;
  case RT_HL: {
    return this->_context_ptr->_bus_ptr->bus_read(this->_context_ptr->_cpu_ptr->cpu_read_reg(RT_HL));
  }
  default:
    printf("**ERR INVALID REG8: %d\n", rt);
    NO_IMPL
      }
}

void pbg_cpu::cpu_set_reg8(reg_type rt, uint8_t val) {
  switch(rt) {
  case RT_A: this->_regs.a = val & 0xFF; break;
  case RT_F: this->_regs.f = val & 0xFF; break;
  case RT_B: this->_regs.b = val & 0xFF; break;
  case RT_C: this->_regs.c = val & 0xFF; break;
  case RT_D: this->_regs.d = val & 0xFF; break;
  case RT_E: this->_regs.e = val & 0xFF; break;
  case RT_H: this->_regs.h = val & 0xFF; break;
  case RT_L: this->_regs.l = val & 0xFF; break;
  case RT_HL: this->_context_ptr->_bus_ptr->bus_write(this->_context_ptr->_cpu_ptr->cpu_read_reg(RT_HL), val); break;
  default:
    printf("**ERR INVALID REG8: %d\n", rt);
    NO_IMPL
      }
}

uint8_t pbg_cpu::cpu_get_int_flags() {
  return this->_int_flags;
}

void pbg_cpu::cpu_set_int_flags(uint8_t value) {
  this->_int_flags = value;
}
