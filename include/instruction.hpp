#ifndef		___INSTRUCTION_HPP___
#define		___INSTRUCTION_HPP___
#include <map>
#include "common.hpp"
#include "enum.hpp"
#include "cpu.hpp"

namespace pandaboygba
{
  class pbg_context;
  class pbg_instruction
  {
  private:
    std::map<int, instruction_t>	        _instructions;
    pbg_context *		_context_ptr;
  public:
    pbg_instruction(pbg_context *);
    ~pbg_instruction();
    instruction_t *instruction_by_opcode(uint8_t opcode);
    char *inst_name(in_type t);
    void inst_to_str(char *str);
  };
}
#endif
