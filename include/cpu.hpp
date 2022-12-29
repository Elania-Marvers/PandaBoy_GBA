#ifndef		___CPU_HPP___
#define		___CPU_HPP___
#include "common.hpp"
#include "register.hpp"
#include "context.hpp"
#include <stdbool.h>
#define CPU_DEBUG 0
#define CPU_FLAG_Z BIT(ctx->regs.f, 7)
#define CPU_FLAG_N BIT(ctx->regs.f, 6)
#define CPU_FLAG_H BIT(ctx->regs.f, 5)
#define CPU_FLAG_C BIT(ctx->regs.f, 4)
//typedef void (*IN_PROC)(cpu_context *);


namespace pandaboygba
{
  class  pbg_cpu
  {
  private:
    pbg_context	*	_context_ptr;
    t_register		_regs;
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

    /*    
    IN_PROC inst_get_processor(in_type type);

    uint16_t cpu_read_reg(reg_type rt);
    void cpu_set_reg(reg_type rt, u16 val);

    u8 cpu_get_ie_register();
    void cpu_set_ie_register(u8 n);

    u8 cpu_read_reg8(reg_type rt);
    void cpu_set_reg8(reg_type rt, u8 val);

    u8 cpu_get_int_flags();
    void cpu_set_int_flags(u8 value);

    void inst_to_str(cpu_context *ctx, char *str);
    */
  };
}

#endif
