#include <iostream>
#include "cpu.h"

rc_e CPU::fetch()
{
   return SUCCESS;
}
 
rc_e CPU::decode()
{
   return SUCCESS;
}

rc_e CPU::execute()
{
   opcodes.opcode_table[OP_00E0](0, 0, 0);
   opcodes.opcode_table[OP_00E0+1](0, 0, 0);
   opcodes.opcode_table[OP_00E0+2](0, 0, 0);
   return SUCCESS;
}
