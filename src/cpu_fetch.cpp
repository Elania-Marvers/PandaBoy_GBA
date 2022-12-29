#include "cpu.hpp"

using namespace pandaboygba;

void pbg_cpu::fetch_data() {
  this->_mem_dest = 0;
  this->_dest_is_mem = false;
  if (this->_cur_inst == NULL) {
    return;
  }
  switch(this->_cur_inst->_mode) {
  case AM_IMP: return;
  case AM_R:
    this->_fetched_data = this->cpu_read_reg(this->_cur_inst->_reg_1);
    return;
  case AM_R_R:
    this->_fetched_data = this->cpu_read_reg(this->_cur_inst->_reg_2);
    return;
  case AM_R_D8:
    this->_fetched_data = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc);
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    this->_regs.pc++;
    return;
  case AM_R_D16:
  case AM_D16: {
    uint16_t lo = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc);
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    uint16_t hi = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc + 1);
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    this->_fetched_data = lo | (hi << 8);
    this->_regs.pc += 2;
    return;
  }
  case AM_MR_R:
    this->_fetched_data = this->_context_ptr->_cpu_ptr->cpu_read_reg(this->_cur_inst->_reg_2);
    this->_mem_dest = this->_context_ptr->_cpu_ptr->cpu_read_reg(this->_cur_inst->_reg_1);
    this->_dest_is_mem = true;
    if (this->_cur_inst->_reg_1 == RT_C) {
      this->_mem_dest |= 0xFF00;
    }
    return;
  case AM_R_MR: {
    uint16_t addr = this->_context_ptr->_cpu_ptr->cpu_read_reg(this->_cur_inst->_reg_2);
    if (this->_cur_inst->_reg_2 == RT_C) {
      addr |= 0xFF00;
    }
    this->_fetched_data = this->_context_ptr->_bus_ptr->bus_read(addr);
    this->_context_ptr->_emu_ptr->emu_cycles(1);
  } return;

  case AM_R_HLI:
    this->_fetched_data = this->_context_ptr->_bus_ptr->bus_read(this->_context_ptr->_cpu_ptr->cpu_read_reg(this->_cur_inst->_reg_2));
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    this->_context_ptr->_cpu_ptr->cpu_set_reg(RT_HL, this->_context_ptr->_cpu_ptr->cpu_read_reg(RT_HL) + 1);
    return;
  case AM_R_HLD:
    this->_fetched_data = this->_context_ptr->_bus_ptr->bus_read(this->_context_ptr->_cpu_ptr->cpu_read_reg(this->_cur_inst->_reg_2));
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    this->_context_ptr->_cpu_ptr->cpu_set_reg(RT_HL, this->_context_ptr->_cpu_ptr->cpu_read_reg(RT_HL) - 1);
    return;
  case AM_HLI_R:
    this->_fetched_data = this->_context_ptr->_cpu_ptr->cpu_read_reg(this->_cur_inst->_reg_2);
    this->_mem_dest = this->_context_ptr->_cpu_ptr->cpu_read_reg(this->_cur_inst->_reg_1);
    this->_dest_is_mem = true;
    this->_context_ptr->_cpu_ptr->cpu_set_reg(RT_HL, this->_context_ptr->_cpu_ptr->cpu_read_reg(RT_HL) + 1);
    return;

  case AM_HLD_R:
    this->_fetched_data = this->_context_ptr->_cpu_ptr->cpu_read_reg(this->_cur_inst->_reg_2);
    this->_mem_dest = this->_context_ptr->_cpu_ptr->cpu_read_reg(this->_cur_inst->_reg_1);
    this->_dest_is_mem = true;
    this->_context_ptr->_cpu_ptr->cpu_set_reg(RT_HL, this->_context_ptr->_cpu_ptr->cpu_read_reg(RT_HL) - 1);
    return;
  case AM_R_A8:
    this->_fetched_data = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc);
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    this->_regs.pc++;
    return;
  case AM_A8_R:
    this->_mem_dest = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc) | 0xFF00;
    this->_dest_is_mem = true;
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    this->_regs.pc++;
    return;
  case AM_HL_SPR:
    this->_fetched_data = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc);
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    this->_regs.pc++;
    return;
  case AM_D8:
    this->_fetched_data = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc);
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    this->_regs.pc++;
    return;
  case AM_A16_R:
  case AM_D16_R: {
    uint16_t lo = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc);
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    uint16_t hi = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc + 1);
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    this->_mem_dest = lo | (hi << 8);
    this->_dest_is_mem = true;
    this->_regs.pc += 2;
    this->_fetched_data = this->_context_ptr->_cpu_ptr->cpu_read_reg(this->_cur_inst->_reg_2);
  } return;
  case AM_MR_D8:
    this->_fetched_data = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc);
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    this->_regs.pc++;
    this->_mem_dest = this->_context_ptr->_cpu_ptr->cpu_read_reg(this->_cur_inst->_reg_1);
    this->_dest_is_mem = true;
    return;
  case AM_MR:
    this->_mem_dest = this->_context_ptr->_cpu_ptr->cpu_read_reg(this->_cur_inst->_reg_1);
    this->_dest_is_mem = true;
    this->_fetched_data = this->_context_ptr->_bus_ptr->bus_read(this->_context_ptr->_cpu_ptr->cpu_read_reg(this->_cur_inst->_reg_1));
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    return;
  case AM_R_A16: {
    uint16_t lo = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc);
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    uint16_t hi = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc + 1);
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    uint16_t addr = lo | (hi << 8);
    this->_regs.pc += 2;
    this->_fetched_data = this->_context_ptr->_bus_ptr->bus_read(addr);
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    return;
  }
  default:
    printf("Unknown Addressing Mode! %d (%02X)\n", this->_cur_inst->_mode, this->_cur_opcode);
    exit(-7);
    return;
  }
}
