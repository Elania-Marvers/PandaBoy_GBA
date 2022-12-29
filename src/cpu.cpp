#include "cpu.hpp"

using namespace pandaboygba;

/*********************************************************/
/**	Those functions are constructor from the	**/
/**	pbg_cpu class					**/
/*********************************************************/

pbg_cpu::pbg_cpu(pbg_context	*ctx)
  : _context_ptr(ctx)
{
  this->_regs.pc = 0x100;
  this->_regs.sp = 0xFFFE;

  *((short *)&this->_regs.a) = 0xB001;
  *((short *)&this->_regs.b) = 0x1300;
  *((short *)&this->_regs.d) = 0xD800;
  *((short *)&this->_regs.h) = 0x4D01;
  this->_ie_register = 0;
  this->_int_flags = 0;
  this->_int_master_enabled = false;
  this->_enabling_ime = false;
  //  this->_context_ptr->_timer_ptr->timer_get_context()->div = 0xABCC;
}

bool pbg_cpu::cpu_step() {
  std::cout << RED << "Cpu not yet implemented" << DEFAULT << std::endl;
    return false;
}

void pbg_cpu::fetch_instruction() {
  //  this->_cur_opcode = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc++);
  this->_cur_inst = this->_context_ptr->_instruction_ptr->instruction_by_opcode(this->_cur_opcode);
}

uint16_t pbg_cpu::reverse(uint16_t n) {
    return ((n & 0xFF00) >> 8) | ((n & 0x00FF) << 8);
}

t_register *pbg_cpu::cpu_get_regs()
{
  return &(this->_regs);
}
