#include <iostream>
#include "opcodes.h"

/**
 * ============================================================================
 * 
 * @name       op_null
 * 
 * @brief      OPCODE 0000
 *             NULL opcode. Useful for debugging
 * 
 * @param[in]  uint16_t NULL (Not used)
 * @param[in]  uint16_t NULL (Not used)
 * @param[in]  uint16_t NULL (Not used)
 * 
 * @return    void
 * 
 * ============================================================================
*/
static void op_null(uint16_t opcode, CPU *cpu)
{
   std::cout << "NULL\n";
}

/**
 * ============================================================================
 * 
 * @name       op_clear
 * 
 * @brief      OPCODE 00E0
 *             Clear the screen
 * 
 * @param[in]  uint16_t NULL (Not used)
 * @param[in]  uint16_t NULL (Not used)
 * @param[in]  uint16_t NULL (Not used)
 * 
 * @return    void
 * 
 * ============================================================================
*/
static void op_clear(uint16_t opcode, CPU *cpu)
{
   std::cout << "CLEAR\n";
}

/**
 * ============================================================================
 * 
 * @name       op_return
 * 
 * @brief      OPCODE 00EE
 *             Exit a subroutine
 * 
 * @param[in]  uint16_t opcode - The opcode being used
 * @param[in]  uint16_t NULL (Not used)
 * @param[in]  uint16_t NULL (Not used)
 * @param[in]  uint16_t NULL (Not used)
 * 
 * @return    void
 * 
 * ============================================================================
*/
static void op_return(uint16_t opcode, CPU *cpu)
{
   std::cout << "RETURN\n";
}

/**
 * ============================================================================
 * 
 * @name       op_jump
 * 
 * @brief      OPCODE 1NNN
 *             JUMP to a specific memory location
 * 
 * @param[in]  uint16_t NNN
 * @param[in]  uint16_t NULL (Not used)
 * @param[in]  uint16_t NULL (Not used)
 * 
 * @return    void
 * 
 * ============================================================================
*/
static void op_jump(uint16_t opcode, CPU *cpu)
{
   std::cout << "JUMP\n";
}

static void (*opcode_table[NUM_OF_OPCODES])(uint16_t, CPU*) =
{
   op_clear, op_return, op_jump, op_null, op_null, op_null, op_null, op_null,
   op_null,  op_null,   op_null, op_null, op_null, op_null, op_null, op_null,
   op_null,  op_null,   op_null, op_null, op_null, op_null, op_null, op_null,
   op_null,  op_null,   op_null, op_null, op_null, op_null, op_null, op_null,
   op_null,  op_null,   op_null
};

/**
 * ============================================================================
 * 
 * @name       execute_opcode
 * 
 * @brief      Execute an opcode instruction
 * 
 * @param[in]  uint16_t opcode - The opcode being used
 * @param[in]  uint16_t op_one - first operand. Up to uint16_t NNN 
 * 
 * @return    void
 * 
 * ============================================================================
*/
rc_e execute_opcode(uint16_t opcode, CPU *cpu)
{
   rc_e     rc           = SUCCESS;
   uint16_t opcode_entry = 0;

   opcode_entry = GET_FIRST_NIBBLE(opcode);
   opcode_table[opcode_entry](opcode, cpu);

   return rc;
}
