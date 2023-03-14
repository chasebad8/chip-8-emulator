#include <iostream>
#include "cpu.h"
#include "opcodes.h"

/**
 * ============================================================================
 * 
 * @name       set_reg
 * 
 * @brief      Set a CPU register value
 * 
 * @param[in]  reg_index - index of the CPU registers
 * @param[in]  value - the value to write into the CPU reg
 * 
 * @return    void
 * 
 * ============================================================================
*/
rc_e CPU::set_reg(reg_index_t reg_index, uint8_t value)
{
   reg[reg_index] = value;
   return SUCCESS;
}

/**
 * ============================================================================
 * 
 * @name       get_reg
 * 
 * @brief      get a CPU register value
 * 
 * @param[in]  reg_index - index of the CPU registers
 * 
 * 
 * @return    reg_val_t
 * 
 * ============================================================================
*/
reg_val_t CPU::get_reg(reg_index_t reg_index)
{
   return reg[reg_index];
}

/**
 * ============================================================================
 * 
 * @name       set_i_reg
 * 
 * @brief      set the current memory value in I reg
 * 
 * @param[in] value - the memory location to set I reg to
 * 
 * @return    rc_e
 * 
 * ============================================================================
*/
rc_e CPU::set_i_reg(mem_val_t value)
{
   i_reg = value;
   return SUCCESS;
}

/**
 * ============================================================================
 * 
 * @name       get_i_reg
 * 
 * @brief      get the current memory location stored in I reg
 *  * 
 * @return    pc_val_t
 * 
 * ============================================================================
*/
mem_val_t CPU::get_i_reg()
{
   return i_reg;
}

/**
 * ============================================================================
 * 
 * @name       mem_stack_push
 * 
 * @brief      Push the inputted argument on to the stack
 * 
 * @param[in] mem_val - the memory location to put on the stack
 *
 * @return    rc_e
 * 
 * ============================================================================
*/
rc_e CPU::mem_stack_push(mem_val_t mem_val)
{
   mem_stack.push(mem_val);
   return SUCCESS;
}

/**
 * ============================================================================
 * 
 * @name       mem_stack_pop
 * 
 * @brief      Pop the top value off of the stack
 *  * 
 * @return    rc_e
 * 
 * ============================================================================
*/
rc_e CPU::mem_stack_pop()
{
   mem_stack.pop();
   return SUCCESS;
}

/**
 * ============================================================================
 * 
 * @name       mem_stack_top
 * 
 * @brief      get the top value from the stack
 *  * 
 * @return    mem_val_t
 * 
 * ============================================================================
*/
mem_val_t CPU::mem_stack_top()
{
   return mem_stack.top();
}

/**
 * ============================================================================
 * 
 * @name       set_pc
 * 
 * @brief      set the current location of the program counter
 * 
 * @param[in] value - the memory location to set PC to
 * 
 * @return    rc_e
 * 
 * ============================================================================
*/
rc_e CPU::set_pc(uint16_t value)
{
   pc = value;
   return SUCCESS;
}

/**
 * ============================================================================
 * 
 * @name       set_pc_plus_offset
 * 
 * @brief      skip 1 instruction
 * 
 * @param[in] value - the memory location to set PC to
 * 
 * @return    rc_e
 * 
 * ============================================================================
*/
rc_e CPU::set_pc_plus_offset(uint16_t value)
{
   pc = pc + value;
   return SUCCESS;
}

/**
 * ============================================================================
 * 
 * @name       get_pc
 * 
 * @brief      get the current location of the program counter
 *  * 
 * @return    pc_val_t
 * 
 * ============================================================================
*/
pc_val_t CPU::get_pc()
{
   return pc;
}

/**
 * ============================================================================
 * 
 * @name       get_mem
 * 
 * @brief      get the 8 bit value in the memory register mem_index
 * 
 * @param[in]  reg_index - index of the CPU registers
 *
 * @return     mem_val_t
 * 
 * ============================================================================
*/
mem_val_t CPU::get_mem(mem_index_t mem_index)
{
   return mem[mem_index];
}

/**
 * ============================================================================
 * 
 * @name      fetch
 * 
 * @brief     fetch an instruction from memory
 * 
 * @return    rc_e
 * 
 * ============================================================================
*/
rc_e CPU::fetch()
{
   return SUCCESS;
}

/**
 * ============================================================================
 * 
 * @name       decode_execute
 * 
 * @brief      decode and execute an opcode instruction
 * 
 * @param[out] value - the memory location inside PC
 * 
 * @return    rc_e
 * 
 * ============================================================================
*/
rc_e CPU::decode_execute()
{
   uint16_t opcode = 0xBABC;
   execute_opcode(opcode, this);

   return SUCCESS;
}

/**
 * ============================================================================
 * 
 * @name       CPU
 * 
 * @brief      No argument constructor for the CPU class
 *  * 
 * @return    none
 * 
 * ============================================================================
*/
CPU::CPU()
{
   std::cout << "Initializing CPU ...\n";
   /* Initially set all RAM to 0 */
   std::fill(std::begin(mem), std::end(mem), 0x00);
   std::fill(std::begin(reg), std::end(reg), 0x00);
}