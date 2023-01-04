#include "cpu.hpp"

using namespace pandaboygba;

/*********************************************************/
/**	Those functions are constructor from the	**/
/**	pbg_cpu class					**/
/*********************************************************/

static pbg_cpu * cpu_ctx;

pbg_cpu::pbg_cpu(pbg_context	*ctx)
  : _context_ptr(ctx)
{
  std::cout << "🎮 " << RED << "[" << ORANGE << "Running CPU!" << RED << "]" << DEFAULT << " 🎮" << std::endl;
  cpu_ctx = this;
  this->_regs.a = 0x01;
  this->_regs.f = 0xB0;
  this->_regs.b = 0x00;
  this->_regs.c = 0x13;
  this->_regs.d = 0x00;
  this->_regs.e = 0xD8;
  this->_regs.h = 0x01;
  this->_regs.l = 0x4D;
  this->_regs.pc = 0x100;
  this->_regs.sp = 0xFFFE;
  this->_ie_register = 0;
  this->_halted = false;
  this->_int_flags = 0;
  this->_int_master_enabled = false;
  this->_enabling_ime = false;
  this->_context_ptr->_timer_ptr->timer_get_context()->_div = 0xABCC;
}

bool pbg_cpu::cpu_step() {
  if (!this->_halted) {
    uint16_t pc = this->_regs.pc;
    this->fetch_instruction();
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    this->fetch_data();
    /*
      if (this->_context_ptr->_ui_ptr->_ticks > 986000 && 
      this->_context_ptr->_ui_ptr->_ticks < 986184
      )
      printf("CTX FD [%04X]\n", this->_fetched_data);
    */
#if CPU_DEBUG == 1
    char flags[16];
    sprintf(flags, "%c%c%c%c", 
            this->_regs.f & (1 << 7) ? 'Z' : '-',
            this->_regs.f & (1 << 6) ? 'N' : '-',
            this->_regs.f & (1 << 5) ? 'H' : '-',
            this->_regs.f & (1 << 4) ? 'C' : '-'
	    );

    char inst[16];
    this->_context_ptr->_instruction_ptr->inst_to_str(inst);
    /*    if (this->_context_ptr->_ui_ptr->_ticks > 986000 && 
	  this->_context_ptr->_ui_ptr->_ticks < 986184
	  )*/
    printf("%08lX %d - %04X: %-12s (%02X %02X %02X) A: %02X F: %s BC: %02X%02X DE: %02X%02X HL: %02X%02X\n", 
	   this->_context_ptr->_ui_ptr->_ticks, this->_context_ptr->_ui_ptr->_ticks, 
	   pc, inst, this->_cur_opcode,
	   this->_context_ptr->_bus_ptr->bus_read(pc + 1),
	   this->_context_ptr->_bus_ptr->bus_read(pc + 2),
	   this->_regs.a, flags, this->_regs.b, this->_regs.c,
	   this->_regs.d, this->_regs.e, this->_regs.h, this->_regs.l);
#endif
    if (this->_cur_inst == NULL) {
      printf("Unknown Instruction! %02X\n", this->_cur_opcode);
      exit(-7);
    }
    this->_context_ptr->_dbg_ptr->dbg_update();
    this->_context_ptr->_dbg_ptr->dbg_print();
    this->execute();
  } else {
    //is halted...
    this->_context_ptr->_emu_ptr->emu_cycles(1);
    if (this->_int_flags)
      this->_halted = false;
  }
  if (this->_int_master_enabled) {
    this->_context_ptr->_interrupts_ptr->cpu_handle_interrupts();
    this->_enabling_ime = false;
  }
  if (this->_enabling_ime) 
    this->_int_master_enabled = true;
  return true;
}

void pbg_cpu::fetch_instruction() {
  this->_cur_opcode = this->_context_ptr->_bus_ptr->bus_read(this->_regs.pc++);
  this->_cur_inst = this->_context_ptr->_instruction_ptr->instruction_by_opcode(this->_cur_opcode);
}

void pbg_cpu::execute()
{
  IN_PROC proc = this->inst_get_processor(this->_cur_inst->_type);
  if (!proc) 
    NO_IMPL
      (this->*proc)();
}

uint8_t pbg_cpu::cpu_get_ie_register() {
  return this->_ie_register;
}

void pbg_cpu::cpu_set_ie_register(uint8_t n) {
  this->_ie_register = n;
}

void pbg_interrupts::cpu_request_interrupt(interrupt_type t) {
  this->_context_ptr->_cpu_ptr->_int_flags |= t;
}

pandaboygba::pbg_cpu * pandaboygba::cpu_get_ctx()
{
  return cpu_ctx;
}


