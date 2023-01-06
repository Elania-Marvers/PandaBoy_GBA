#ifndef		___CPU_HPP___
#define		___CPU_HPP___
#include "common.hpp"
#include "register.hpp"
#include "enum.hpp"
#include "context.hpp"
#include <stdbool.h>
#define CPU_DEBUG 0
#define CPU_FLAG_Z BIT(cpu_get_ctx()->_regs.f, 7)
#define CPU_FLAG_N BIT(cpu_get_ctx()->_regs.f, 6)
#define CPU_FLAG_H BIT(cpu_get_ctx()->_regs.f, 5)
#define CPU_FLAG_C BIT(cpu_get_ctx()->_regs.f, 4)
namespace pandaboygba { class pbg_cpu; }
typedef void (pandaboygba::pbg_cpu::* IN_PROC)();

namespace pandaboygba
{
  class pbg_context;
  class  pbg_cpu
  {
  public:
    t_register		_regs;
    pbg_context	*	_context_ptr;
    uint16_t		_fetched_data;
    uint16_t		_mem_dest;
    bool		_dest_is_mem;
    uint8_t		_cur_opcode;
    instruction_t *	_cur_inst;
    bool		_halted;
    bool		_stepping;
    bool		_int_master_enabled;
    bool		_enabling_ime;
    uint8_t		_ie_register;
    uint8_t		_int_flags;

    uint16_t reverse (uint16_t n);
    void fetch_instruction();
    
  public:
    pbg_cpu(pbg_context	*);
    bool cpu_step();
    t_register *cpu_get_regs();
    void fetch_data();
    void execute();
    uint16_t cpu_read_reg(reg_type rt);
    void cpu_set_reg(reg_type rt, uint16_t val);
    uint8_t cpu_get_ie_register();
    void cpu_set_ie_register(uint8_t n);
    uint8_t cpu_read_reg8(reg_type rt);
    void cpu_set_reg8(reg_type rt, uint8_t val);
    uint8_t cpu_get_int_flags();
    void cpu_set_int_flags(uint8_t value);
    void cpu_set_flags(int8_t z, int8_t n, int8_t h, int8_t c);
    IN_PROC inst_get_processor(in_type type);
    void inst_to_str(char *str);


    /****PROC****/
    void proc_none();
    void proc_nop();
    reg_type decode_reg(uint8_t reg);
    void proc_cb();
    void proc_rlca();
    void proc_rrca();
    void proc_rla();
    void proc_stop();
    void proc_daa();
    void proc_cpl();
    void proc_scf();
    void proc_ccf();
    void proc_halt();
    void proc_rra();
    void proc_and();
    void proc_xor();
    void proc_or();
    void proc_cp();
    void proc_di();
    void proc_ei();
    bool is_16_bit(reg_type rt);
    void proc_ld();
    void proc_ldh();
    bool check_cond();
    void goto_addr(uint16_t addr, bool pushpc);
    void proc_jp();
    void proc_jr();
    void proc_call();
    void proc_rst();
    void proc_ret();
    void proc_reti();
    void proc_pop();
    void proc_push();
    void proc_inc();
    void proc_dec();
    void proc_sub();
    void proc_sbc();
    void proc_adc();
    void proc_add();
    
    /****PROC****/

    
  };
  pbg_cpu * cpu_get_ctx();
}



#endif
