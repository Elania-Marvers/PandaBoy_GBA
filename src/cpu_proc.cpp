#include "cpu.hpp"

using namespace pandaboygba;
//processes CPU instructions...
void pbg_cpu::cpu_set_flags(int8_t z, int8_t n, int8_t h, int8_t c)
{
  if (z != -1)
    BIT_SET(this->_regs.f, 7, z);
  if (n != -1) 
    BIT_SET(this->_regs.f, 6, n);
  if (h != -1)
    BIT_SET(this->_regs.f, 5, h);
  if (c != -1)
    BIT_SET(this->_regs.f, 4, c);
}

void pbg_cpu::proc_none()
{
  std::cout << "INVALID INSTRUCTION!" << std::endl;
  exit(-7);
}
void pbg_cpu::proc_nop()
{

}

reg_type rt_lookup[] = {
  RT_B,
  RT_C,
  RT_D,
  RT_E,
  RT_H,
  RT_L,
  RT_HL,
  RT_A
};

reg_type pbg_cpu::decode_reg(uint8_t reg)
{
  if (reg > 0b111)
    return RT_NONE;
  return rt_lookup[reg];
}

void pbg_cpu::proc_cb()
{
  // printf("cb0 a[%04X] FD[%04X]\n", this->_regs.a, this->_fetched_data);
  uint8_t op = this->_fetched_data;
  reg_type reg = this->decode_reg(op & 0b111);
  uint8_t bit = (op >> 3) & 0b111;
  uint8_t bit_op = (op >> 6) & 0b11;
  uint8_t reg_val = this->cpu_read_reg8(reg);
  this->_context_ptr->_emu_ptr->emu_cycles(1);
  if (reg == RT_HL) {
    this->_context_ptr->_emu_ptr->emu_cycles(2);
  }

  //     printf("cb1 a[%04X] FD[%04X] op[%04X] reg[%04X] bit[%04X] bit_op[%04X] reg_val[%04X]\n", this->_regs.a, this->_fetched_data, op, reg, bit, bit_op, reg_val);
  switch(bit_op) {
  case 1:
    //BIT
    this->cpu_set_flags(!(reg_val & (1 << bit)), 0, 1, -1);
    return;
  case 2:
    //RST
    reg_val &= ~(1 << bit);
    this->cpu_set_reg8(reg, reg_val);
    // printf("reg_val[%04X]\n", reg_val);
    // printf("cb2 a[%04X] FD[%04X] op[%04X] reg[%04X] bit[%04X] bit_op[%04X] reg_val[%04X]\n", this->_regs.a, this->_fetched_data, op, reg, bit, bit_op, reg_val);

    return;
  case 3:
    //SET
    reg_val |= (1 << bit);
    this->cpu_set_reg8(reg, reg_val);
    return;
  }

  bool flagC = CPU_FLAG_C;
  switch(bit) {
  case 0: {
    //RLC
    bool setC = false;
    uint8_t result = (reg_val << 1) & 0xFF;
    if ((reg_val & (1 << 7)) != 0) {
      result |= 1;
      setC = true;
    }
    this->cpu_set_reg8(reg, result);
    this->cpu_set_flags(result == 0, false, false, setC);
  } return;
  case 1: {
    //RRC
    uint8_t old = reg_val;
    reg_val >>= 1;
    reg_val |= (old << 7);
    this->cpu_set_reg8(reg, reg_val);
    this->cpu_set_flags(!reg_val, false, false, old & 1);
  } return;
  case 2: {
    //RL
    uint8_t old = reg_val;
    reg_val <<= 1;
    reg_val |= flagC;
    this->cpu_set_reg8(reg, reg_val);
    this->cpu_set_flags(!reg_val, false, false, !!(old & 0x80));
  } return;
  case 3: {
    //RR
    uint8_t old = reg_val;
    reg_val >>= 1;
    reg_val |= (flagC << 7);
    this->cpu_set_reg8(reg, reg_val);
    this->cpu_set_flags(!reg_val, false, false, old & 1);
  } return;
  case 4: {
    //SLA
    uint8_t old = reg_val;
    reg_val <<= 1;
    this->cpu_set_reg8(reg, reg_val);
    this->cpu_set_flags(!reg_val, false, false, !!(old & 0x80));
  } return;
  case 5: {
    //SRA
    uint8_t u = (int8_t)reg_val >> 1;
    this->cpu_set_reg8(reg, u);
    this->cpu_set_flags(!u, 0, 0, reg_val & 1);
  } return;
  case 6: {
    //SWAP
    reg_val = ((reg_val & 0xF0) >> 4) | ((reg_val & 0xF) << 4);
    this->cpu_set_reg8(reg, reg_val);
    this->cpu_set_flags(reg_val == 0, false, false, false);
  } return;
  case 7: {
    //SRL
    uint8_t u = reg_val >> 1;
    this->cpu_set_reg8(reg, u);
    this->cpu_set_flags(!u, 0, 0, reg_val & 1);
  } return;
  }
  fprintf(stderr, "ERROR: INVALID CB: %02X", op);
  NO_IMPL
    }

void pbg_cpu::proc_rlca()
{
  uint8_t u = this->_regs.a;
  bool c = (u >> 7) & 1;
  u = (u << 1) | c;
  this->_regs.a = u;
  this->cpu_set_flags(0, 0, 0, c);
}

void pbg_cpu::proc_rrca()
{
  uint8_t b = this->_regs.a & 1;
  this->_regs.a >>= 1;
  this->_regs.a |= (b << 7);
  this->cpu_set_flags(0, 0, 0, b);
}

void pbg_cpu::proc_rla()
{
  uint8_t u = this->_regs.a;
  uint8_t cf = CPU_FLAG_C;
  uint8_t c = (u >> 7) & 1;
  this->_regs.a = (u << 1) | cf;
  this->cpu_set_flags(0, 0, 0, c);
}

void pbg_cpu::proc_stop()
{
  fprintf(stderr, "STOPPING!\n");
}

void pbg_cpu::proc_daa()
{
  uint8_t u = 0;
  int fc = 0;
  if (CPU_FLAG_H || (!CPU_FLAG_N && (this->_regs.a & 0xF) > 9))
    u = 6;
  if (CPU_FLAG_C || (!CPU_FLAG_N && this->_regs.a > 0x99))
    {
      u |= 0x60;
      fc = 1;
    }
  this->_regs.a += CPU_FLAG_N ? -u : u;
  this->cpu_set_flags(this->_regs.a == 0, -1, 0, fc);
}

void pbg_cpu::proc_cpl()
{
  this->_regs.a = ~this->_regs.a;
  this->cpu_set_flags(-1, 1, 1, -1);
}

void pbg_cpu::proc_scf()
{
  this->cpu_set_flags(-1, 0, 0, 1);
}

void pbg_cpu::proc_ccf()
{
  this->cpu_set_flags(-1, 0, 0, CPU_FLAG_C ^ 1);
}

void pbg_cpu::proc_halt()
{
  this->_halted = true;
}

void pbg_cpu::proc_rra()
{
  uint8_t carry = CPU_FLAG_C;
  uint8_t new_c = this->_regs.a & 1;
  this->_regs.a >>= 1;
  this->_regs.a |= (carry << 7);
  this->cpu_set_flags(0, 0, 0, new_c);
}

void pbg_cpu::proc_and()
{
  this->_regs.a &= this->_fetched_data;
  this->cpu_set_flags(this->_regs.a == 0, 0, 1, 0);
}

void pbg_cpu::proc_xor()
{
  this->_regs.a ^= this->_fetched_data & 0xFF;
  this->cpu_set_flags(this->_regs.a == 0, 0, 0, 0);
}

void pbg_cpu::proc_or()
{
  this->_regs.a |= this->_fetched_data & 0xFF;
  this->cpu_set_flags(this->_regs.a == 0, 0, 0, 0);
}

void pbg_cpu::proc_cp()
{
  //printf("a[%04X] FD[%04X]\n", this->_regs.a, this->_fetched_data);
  int n = (int)this->_regs.a - (int) this->_fetched_data; //int
  //   printf("n == %04X\n", n);
  this->cpu_set_flags(n == 0, 1, 
		      ((int)this->_regs.a & 0x0F) - ((int)this->_fetched_data & 0x0F) < 0, n < 0);
}

void pbg_cpu::proc_di()
{
  this->_int_master_enabled = false;
}

void pbg_cpu::proc_ei()
{
  this->_enabling_ime = true;
}

bool pbg_cpu::is_16_bit(reg_type rt)
{
  return rt >= RT_AF;
}

void pbg_cpu::proc_ld()
{
  if (this->_dest_is_mem)
    {
      //LD (BC), A for instance...
      if (this->is_16_bit(this->_cur_inst->_reg_2))
	{
	  //if 16 bit register...
	  this->_context_ptr->_emu_ptr->emu_cycles(1);
	  this->_context_ptr->_bus_ptr->bus_write16(this->_mem_dest, this->_fetched_data);
        } else {

	this->_context_ptr->_bus_ptr->bus_write(this->_mem_dest, this->_fetched_data);
      }
      this->_context_ptr->_emu_ptr->emu_cycles(1);
      return;
    }
  if (this->_cur_inst->_mode == AM_HL_SPR) {
    uint8_t hflag = (this->cpu_read_reg(this->_cur_inst->_reg_2) & 0xF) + (this->_fetched_data & 0xF) >= 0x10;
    uint8_t cflag = (this->cpu_read_reg(this->_cur_inst->_reg_2) & 0xFF) + (this->_fetched_data & 0xFF) >= 0x100;
    this->cpu_set_flags(0, 0, hflag, cflag);
    this->cpu_set_reg(this->_cur_inst->_reg_1, this->cpu_read_reg(this->_cur_inst->_reg_2) + (int8_t) this->_fetched_data);
    return;
  }
  /*
    if (this->_context_ptr->_ui_ptr->_ticks > 986000 && 
    this->_context_ptr->_ui_ptr->_ticks < 986184
    )
    printf("REG1[%04X] FD[%04X]\n", this->_cur_inst->_reg_1, this->_fetched_data);*/
  this->cpu_set_reg(this->_cur_inst->_reg_1, this->_fetched_data);
}

void pbg_cpu::proc_ldh()
{
  if (this->_cur_inst->_reg_1 == RT_A)
    {
      //  printf("ldh1 a[%04X] FD[%04X] REG1[%04X] BR[%04X]\n", this->_regs.a, this->_fetched_data, this->_cur_inst->_reg_1, this->_context_ptr->_bus_ptr->bus_read(0xFF00 | this->_fetched_data));
      this->cpu_set_reg(this->_cur_inst->_reg_1, this->_context_ptr->_bus_ptr->bus_read(0xFF00 | this->_fetched_data));
      //  printf("ldh1 a[%04X] FD[%04X] REG1[%04X] BR[%04X]\n", this->_regs.a, this->_fetched_data, this->_cur_inst->_reg_1, this->_context_ptr->_bus_ptr->bus_read(0xFF00 | this->_fetched_data));
    }
  else {
    //     printf("ldh2 mem_dest[%04X] regA[%04X]\n", this->_mem_dest, this->_regs.a);
    this->_context_ptr->_bus_ptr->bus_write(this->_mem_dest, this->_regs.a);
       
  }


  this->_context_ptr->_emu_ptr->emu_cycles(1);
  //printf("ldh3 a[%04X] FD[%04X]\n", this->_regs.a, this->_fetched_data);
}


bool pbg_cpu::check_cond()
{
  bool z = CPU_FLAG_Z;
  bool c = CPU_FLAG_C;
  switch(this->_cur_inst->_cond){
  case CT_NONE: return true;
  case CT_C: return c;
  case CT_NC: return !c;
  case CT_Z: return z;
  case CT_NZ: return !z;
  }
  return false;
}

void pbg_cpu::goto_addr(uint16_t addr, bool pushpc)
{
  if (this->check_cond())
    {
      if (pushpc)
	{
	  this->_context_ptr->_emu_ptr->emu_cycles(2);
	  this->_context_ptr->_stack_ptr->stack_push16(this->_regs.pc);
        }
      this->_regs.pc = addr;
      this->_context_ptr->_emu_ptr->emu_cycles(1);
      //printf("PC[%04X]\n", this->_regs.pc);
    }
}

void pbg_cpu::proc_jp()
{
  this->goto_addr(this->_fetched_data, false);
}

void pbg_cpu::proc_jr()
{
  int8_t rel = (int8_t) (this->_fetched_data & 0xFF);
  uint16_t addr = this->_regs.pc + rel;
  this->goto_addr(addr, false);
}

void pbg_cpu::proc_call()
{
  this->goto_addr(this->_fetched_data, true);
}

void pbg_cpu::proc_rst()
{
  this->goto_addr(this->_cur_inst->_param, true);
}

void pbg_cpu::proc_ret()
{
  /*      if (this->_context_ptr->_ui_ptr->_ticks > 986000 && 
	  this->_context_ptr->_ui_ptr->_ticks < 986184
	  ){
	  printf("cond[%04X] ccond[%04X] \n", this->_cur_inst->_cond, this->check_cond());
	  }*/
  if (this->_cur_inst->_cond != CT_NONE)
    this->_context_ptr->_emu_ptr->emu_cycles(1);
  if (this->check_cond())
    {
      uint16_t lo = this->_context_ptr->_stack_ptr->stack_pop();
      this->_context_ptr->_emu_ptr->emu_cycles(1);
      uint16_t hi = this->_context_ptr->_stack_ptr->stack_pop();
      this->_context_ptr->_emu_ptr->emu_cycles(1);
      uint16_t n = (hi << 8) | lo;
      this->_regs.pc = n;
      this->_context_ptr->_emu_ptr->emu_cycles(1);
      /*      if (this->_context_ptr->_ui_ptr->_ticks > 986000 && 
	      this->_context_ptr->_ui_ptr->_ticks < 986184
	      ){
	      printf("PC[%04X] CPU_FD[%04X] \n", this->_regs.pc, this->_fetched_data);
	      }*/
    }
}

void pbg_cpu::proc_reti()
{
  this->_int_master_enabled = true;
  this->proc_ret();
}

void pbg_cpu::proc_pop()
{
  uint16_t lo = this->_context_ptr->_stack_ptr->stack_pop();
  this->_context_ptr->_emu_ptr->emu_cycles(1);
  uint16_t hi = this->_context_ptr->_stack_ptr->stack_pop();
  this->_context_ptr->_emu_ptr->emu_cycles(1);
  uint16_t n = (hi << 8) | lo;
  this->cpu_set_reg(this->_cur_inst->_reg_1, n);
  if (this->_cur_inst->_reg_1 == RT_AF)
    this->cpu_set_reg(this->_cur_inst->_reg_1, n & 0xFFF0);
}

void pbg_cpu::proc_push()
{//FLAGOE
  uint16_t hi = (this->cpu_read_reg(this->_cur_inst->_reg_1) >> 8) & 0xFF;
  this->_context_ptr->_emu_ptr->emu_cycles(1);
  this->_context_ptr->_stack_ptr->stack_push(hi);
  uint16_t lo = this->cpu_read_reg(this->_cur_inst->_reg_1) & 0xFF;
  this->_context_ptr->_emu_ptr->emu_cycles(1);
  this->_context_ptr->_stack_ptr->stack_push(lo);
  this->_context_ptr->_emu_ptr->emu_cycles(1);
}

void pbg_cpu::proc_inc()
{
  uint16_t val = this->cpu_read_reg(this->_cur_inst->_reg_1) + 1;
  if (this->is_16_bit(this->_cur_inst->_reg_1)) 
    this->_context_ptr->_emu_ptr->emu_cycles(1);
  if (this->_cur_inst->_reg_1 == RT_HL && this->_cur_inst->_mode == AM_MR) {
    val = this->_context_ptr->_bus_ptr->bus_read(cpu_read_reg(RT_HL)) + 1;
    val &= 0xFF;
    this->_context_ptr->_bus_ptr->bus_write(cpu_read_reg(RT_HL), val);
  } else {
    this->cpu_set_reg(this->_cur_inst->_reg_1, val);
    val = this->cpu_read_reg(this->_cur_inst->_reg_1);
  }
  if ((this->_cur_opcode & 0x03) == 0x03) {
    return;
  }
  this->cpu_set_flags(val == 0, 0, (val & 0x0F) == 0, -1);
}

void pbg_cpu::proc_dec()
{
  uint16_t val = this->cpu_read_reg(this->_cur_inst->_reg_1) - 1;
  if (this->is_16_bit(this->_cur_inst->_reg_1))
    this->_context_ptr->_emu_ptr->emu_cycles(1);
  if (this->_cur_inst->_reg_1 == RT_HL && this->_cur_inst->_mode == AM_MR)
    {
      val = this->_context_ptr->_bus_ptr->bus_read(this->cpu_read_reg(RT_HL)) - 1;
      this->_context_ptr->_bus_ptr->bus_write(this->cpu_read_reg(RT_HL), val);
    }
  else
    {
      this->cpu_set_reg(this->_cur_inst->_reg_1, val);
      val = this->cpu_read_reg(this->_cur_inst->_reg_1);
    }
  if ((this->_cur_opcode & 0x0B) == 0x0B)
    return;
  this->cpu_set_flags(val == 0, 1, (val & 0x0F) == 0x0F, -1);
}

void pbg_cpu::proc_sub()
{
  uint16_t val = this->cpu_read_reg(this->_cur_inst->_reg_1) - this->_fetched_data;
  int z = val == 0;
  int h = ((int) this->cpu_read_reg(this->_cur_inst->_reg_1) & 0xF) - ((int) this->_fetched_data & 0xF) < 0;
  int c = ((int) this->cpu_read_reg(this->_cur_inst->_reg_1)) - ((int) this->_fetched_data) < 0;
  this->cpu_set_reg(this->_cur_inst->_reg_1, val);
  this->cpu_set_flags(z, 1, h, c);
}

void pbg_cpu::proc_sbc()
{
  uint8_t val = this->_fetched_data + CPU_FLAG_C;
  int z = this->cpu_read_reg(this->_cur_inst->_reg_1) - val == 0;
  int h = ((int) this->cpu_read_reg(this->_cur_inst->_reg_1) & 0xF) 
    - ((int) this->_fetched_data & 0xF) - ((int) CPU_FLAG_C) < 0;
  int c = ((int) this->cpu_read_reg(this->_cur_inst->_reg_1)) 
    - ((int)this->_fetched_data) - ((int) CPU_FLAG_C) < 0;
  this->cpu_set_reg(this->_cur_inst->_reg_1, this->cpu_read_reg(this->_cur_inst->_reg_1) - val);
  this->cpu_set_flags(z, 1, h, c);
}

void pbg_cpu::proc_adc()
{
  uint16_t u = this->_fetched_data;
  uint16_t a = this->_regs.a;
  uint16_t c = CPU_FLAG_C;
  this->_regs.a = (a + u + c) & 0xFF;
  this->cpu_set_flags(this->_regs.a == 0, 0, 
		      (a & 0xF) + (u & 0xF) + c > 0xF,
		      a + u + c > 0xFF);
}

void pbg_cpu::proc_add()
{
  uint32_t val = this->cpu_read_reg(this->_cur_inst->_reg_1) + this->_fetched_data;
  bool is_16bit = this->is_16_bit(this->_cur_inst->_reg_1);
  if (is_16bit)
    this->_context_ptr->_emu_ptr->emu_cycles(1);
  if (this->_cur_inst->_reg_1 == RT_SP)
    val = this->cpu_read_reg(this->_cur_inst->_reg_1) + (int8_t) this->_fetched_data;
  int z = (val & 0xFF) == 0;
  int h = (this->cpu_read_reg(this->_cur_inst->_reg_1) & 0xF) + (this->_fetched_data & 0xF) >= 0x10;
  int c = (int) (this->cpu_read_reg(this->_cur_inst->_reg_1) & 0xFF) + (int) (this->_fetched_data & 0xFF) >= 0x100;
  if (is_16bit)
    {
      z = -1;
      h = (this->cpu_read_reg(this->_cur_inst->_reg_1) & 0xFFF) + (this->_fetched_data & 0xFFF) >= 0x1000;
      uint32_t n = ((uint32_t) this->cpu_read_reg(this->_cur_inst->_reg_1)) + ((uint32_t) this->_fetched_data);
      c = n >= 0x10000;
    }
  if (this->_cur_inst->_reg_1 == RT_SP)
    {
      z = 0;
      h = (this->cpu_read_reg(this->_cur_inst->_reg_1) & 0xF) + (this->_fetched_data & 0xF) >= 0x10;
      c = (int) (this->cpu_read_reg(this->_cur_inst->_reg_1) & 0xFF) + (int) (this->_fetched_data & 0xFF) >= 0x100;
    }
  this->cpu_set_reg(this->_cur_inst->_reg_1, val & 0xFFFF);
  this->cpu_set_flags(z, 0, h, c);
}

static std::map<int, IN_PROC> processors;

void init_proc()
{
  processors.insert({
      {IN_NONE, &pbg_cpu::proc_none},
      {IN_NOP, &pbg_cpu::proc_nop},
      {IN_LD, &pbg_cpu::proc_ld},
      {IN_LDH, &pbg_cpu::proc_ldh},
      {IN_JP, &pbg_cpu::proc_jp},
      {IN_DI, &pbg_cpu::proc_di},
      {IN_POP, &pbg_cpu::proc_pop},
      {IN_PUSH, &pbg_cpu::proc_push},
      {IN_JR, &pbg_cpu::proc_jr},
      {IN_CALL, &pbg_cpu::proc_call},
      {IN_RET, &pbg_cpu::proc_ret},
      {IN_RST, &pbg_cpu::proc_rst},
      {IN_DEC, &pbg_cpu::proc_dec},
      {IN_INC, &pbg_cpu::proc_inc},
      {IN_ADD, &pbg_cpu::proc_add},
      {IN_ADC, &pbg_cpu::proc_adc},
      {IN_SUB, &pbg_cpu::proc_sub},
      {IN_SBC, &pbg_cpu::proc_sbc},
      {IN_AND, &pbg_cpu::proc_and},
      {IN_XOR, &pbg_cpu::proc_xor},
      {IN_OR, &pbg_cpu::proc_or},
      {IN_CP, &pbg_cpu::proc_cp},
      {IN_CB, &pbg_cpu::proc_cb},
      {IN_RRCA, &pbg_cpu::proc_rrca},
      {IN_RLCA, &pbg_cpu::proc_rlca},
      {IN_RRA, &pbg_cpu::proc_rra},
      {IN_RLA, &pbg_cpu::proc_rla},
      {IN_STOP, &pbg_cpu::proc_stop},
      {IN_HALT, &pbg_cpu::proc_halt},
      {IN_DAA, &pbg_cpu::proc_daa},
      {IN_CPL, &pbg_cpu::proc_cpl},
      {IN_SCF, &pbg_cpu::proc_scf},
      {IN_CCF, &pbg_cpu::proc_ccf},
      {IN_EI, &pbg_cpu::proc_ei},
      {IN_RETI, &pbg_cpu::proc_reti}
    });
}

IN_PROC pbg_cpu::inst_get_processor(in_type type) {
  if (processors.empty())
    init_proc();
  return processors[type];
}

