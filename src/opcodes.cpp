#include <iostream>
#include "opcodes.h"

void (*OPCODES::opcode_table[NUM_OF_OPCODES])(uint16_t, uint16_t, uint16_t) =
{
   OPCODES::op_clear, OPCODES::op_return, OPCODES::op_null, OPCODES::op_null, OPCODES::op_null, OPCODES::op_null, OPCODES::op_null, OPCODES::op_null,
   OPCODES::op_null,  OPCODES::op_null,   OPCODES::op_null, OPCODES::op_null, OPCODES::op_null, OPCODES::op_null, OPCODES::op_null, OPCODES::op_null,
   OPCODES::op_null,  OPCODES::op_null,   OPCODES::op_null, OPCODES::op_null, OPCODES::op_null, OPCODES::op_null, OPCODES::op_null, OPCODES::op_null,
   OPCODES::op_null,  OPCODES::op_null,   OPCODES::op_null, OPCODES::op_null, OPCODES::op_null, OPCODES::op_null, OPCODES::op_null, OPCODES::op_null,
   OPCODES::op_null,  OPCODES::op_null,   OPCODES::op_null
};

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
void OPCODES::op_null(uint16_t, uint16_t, uint16_t)
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
void OPCODES::op_clear(uint16_t, uint16_t, uint16_t)
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
 * @param[in]  uint16_t NULL (Not used)
 * @param[in]  uint16_t NULL (Not used)
 * @param[in]  uint16_t NULL (Not used)
 * 
 * @return    void
 * 
 * ============================================================================
*/
void OPCODES::op_return(uint16_t, uint16_t, uint16_t)
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
void OPCODES::op_jump(uint16_t, uint16_t, uint16_t)
{
   std::cout << "JUMP\n";
}