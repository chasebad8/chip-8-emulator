#include <iostream>
#include "opcodes.h"
#include <cstdlib>
#include <ctime>

#define COMPARE_OPCODES_OFFSET 3
#define INSTRUCTION_SKIP       2
#define MAX_BYTE_VAL           255

/**
 * ============================================================================
 *
 * @name       op_null
 *
 * @brief      OPCODE 0000
 *             NULL opcode. Useful for debugging
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_null(opcode_t opcode, CPU *cpu)
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
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_clear(opcode_t opcode, CPU *cpu)
{
   std::cout << "CLEAR\n";
}

/**
 * ============================================================================
 *
 * @name       op_return
 *
 * @brief      OPCODE 00EE
 *             Exit a subroutine. Restore PC to the memory address that is on
 *             the stack
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_return(opcode_t opcode, CPU *cpu)
{
   std::cout << "RETURN\n";
}

/**
 * ============================================================================
 *
 * @name       op_sys_calls
 *
 * @brief      Handle opcodes in group 0x0XX
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_sys_calls(opcode_t opcode, CPU *cpu)
{
   switch(GET_BYTE_0(opcode))
   {
      case CLEAR:
         op_clear(opcode, cpu);
         break;
      case RETURN:
         op_return(opcode, cpu);
         break;
      default:
         std::cout << "Invalid OP code\n";
         break;
   }
}

/**
 * ============================================================================
 *
 * @name       op_jump
 *
 * @brief      OPCODE 1NNN
 *             JUMP to a specific memory location
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_jump(opcode_t opcode, CPU *cpu)
{
   pc_val_t pc_val = GET_NIBBLE_BYTE(opcode);

   cpu->set_pc((GET_NIBBLE_3(opcode) == OP_1XXX) ? pc_val :
                                                   pc_val + cpu->get_reg(REGISTER_0));
   std::cout << "JUMP\n";
}

/**
 * ============================================================================
 *
 * @name       op_subroutine
 *
 * @brief      OPCODE 2NNN
 *             JUMP to address NNN while pushing current PC value onto the stack
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_subroutine(opcode_t opcode, CPU *cpu)
{
   /* TODO: ADD current PC to stack */
   cpu->set_pc(GET_NIBBLE_BYTE(opcode));
   std::cout << "SUBROUTINE\n";
}

/**
 * ============================================================================
 *
 * @name       op_compare
 *
 * @brief      OPCODE 3XNN, 4XNN, 5XY0
 *             3XNN: Skip the following instruction if the value of register
 *                   VX equals NN
 *             4XNN: Skip the following instruction if the value of register
 *                   VX is not equal to NN
 *             5XY0: Skip the following instruction if the value of register
 *                   VX is equal to the value of register VY
 *             9XY0: Skip the following instruction if the value of register
 *                   VX is not equal to the value of register VY
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_compare(opcode_t opcode, CPU *cpu)
{
   reg_val_t reg_val = cpu->get_reg(GET_NIBBLE_2(opcode));

   switch(GET_NIBBLE_3(opcode))
   {
      case EQUAL:
         if(reg_val == GET_BYTE_0(opcode))
         {
            cpu->set_pc_plus_offset(INSTRUCTION_SKIP);
         }
         break;

      case NOT_EQUAL:
         if(reg_val != GET_BYTE_0(opcode))
         {
            cpu->set_pc_plus_offset(INSTRUCTION_SKIP);
         }
         break;

      case EQUAL_REG:
         if(reg_val == cpu->get_reg(GET_NIBBLE_1(opcode)))
         {
            cpu->set_pc_plus_offset(INSTRUCTION_SKIP);
         }
         break;
      case NOT_EQUAL_REG:
         if(reg_val != cpu->get_reg(GET_NIBBLE_1(opcode)))
         {
            cpu->set_pc_plus_offset(INSTRUCTION_SKIP);
         }
         break;
      default:
         std::cout << "Invalid OP code\n";
         break;
   }
}

/**
 * ============================================================================
 *
 * @name       op_store
 *
 * @brief      OPCODE 6XNN
 *             Store the value of NN in register VX
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_store(opcode_t opcode, CPU *cpu)
{
   switch(GET_NIBBLE_3(opcode))
   {
      case OP_6XXX: cpu->set_reg(GET_NIBBLE_2(opcode), GET_BYTE_0(opcode)); break;
      case OP_AXXX: cpu->set_reg(REGISTER_I, GET_BYTE_0(opcode));           break;
   }
}

/**
 * ============================================================================
 *
 * @name       op_add
 *
 * @brief      OPCODE 7XNN
 *             Add the value of NN in register VX
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_add(opcode_t opcode, CPU *cpu)
{
   reg_val_t reg_val = (cpu->get_reg(GET_NIBBLE_2(opcode)) + GET_BYTE_0(opcode)) % 256;
   cpu->set_reg(GET_NIBBLE_2(opcode), reg_val);
}

/**
 * ============================================================================
 *
 * @name       op_alu_store
 *
 * @brief      OPCODE 8XY0
 *             Store  value of reg Y into reg X
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_alu_store(opcode_t opcode, CPU *cpu)
{
   reg_val_t reg_y = cpu->get_reg(GET_NIBBLE_1(opcode));
   cpu->set_reg(GET_NIBBLE_3(opcode), reg_y);
}

/**
 * ============================================================================
 *
 * @name       op_alu_bitwise
 *
 * @brief      Perform Bitwise operators on reg's VX and VY,
 *             storing resulting value in VX

 *             OPCODE 8XY1: Set VX to VX OR VY
 *             OPCODE 8XY1: Set VX to VX AND VY
 *             OPCODE 8XY1: Set VX to VX XOR VY
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_alu_bitwise(opcode_t opcode, CPU *cpu)
{
   reg_index_t reg_x_index = GET_NIBBLE_2(opcode);
   reg_index_t reg_y_index = GET_NIBBLE_1(opcode);
   reg_val_t   reg_x       = cpu->get_reg(reg_x_index);
   reg_val_t   reg_y       = cpu->get_reg(reg_y_index);

   switch(GET_NIBBLE_0(opcode))
   {
      case ALU_OR:  cpu->set_reg(reg_x_index, (reg_x | reg_y)); break;
      case ALU_AND: cpu->set_reg(reg_x_index, (reg_x & reg_y)); break;
      case ALU_XOR: cpu->set_reg(reg_x_index, (reg_x ^ reg_y)); break;
      default:
         std::cout << "Invalid OP code\n";
         break;
   }
}

/**
 * ============================================================================
 *
 * @name       op_alu_add_sub
 *
 * @brief      Addition and Subtraction to check flags
 *             OPCODE 8XY4: Add VX and VY. Set VFLAG to 01 (carry) if greater
 *                          than the largest number storable in a byte (255)
 *             OPCODE 8XY5: Subtract VY from VX. Set VFLAG to 00 (borrow) if
 *                          the subtraction would result in a negative number
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_alu_add_sub(opcode_t opcode, CPU *cpu)
{
   reg_index_t reg_x_index   = GET_NIBBLE_2(opcode);
   reg_index_t reg_y_index   = GET_NIBBLE_1(opcode);
   reg_val_t   reg_x         = cpu->get_reg(reg_x_index);
   reg_val_t   reg_y         = cpu->get_reg(reg_y_index);
   reg_val_t   new_reg_x_val = 0;

   switch(GET_NIBBLE_0(opcode))
   {
      case ALU_ADD: ((reg_x + reg_y) > MAX_BYTE_VAL) ? cpu->set_reg(VFLAG, VFLAG_CARRY) :
                                                       cpu->set_reg(VFLAG, VFLAG_CLEAR); break;
      case ALU_SUB: ((reg_y - reg_x) < 0) ? cpu->set_reg(VFLAG, VFLAG_BORROW) :
                                            cpu->set_reg(VFLAG, VFLAG_NO_BORROW); break;
      case ALU_STORE: ((new_reg_x_val = reg_y - reg_x) < 0) ? cpu->set_reg(VFLAG, VFLAG_BORROW) :
                                                              cpu->set_reg(VFLAG, VFLAG_NO_BORROW); break;
      default:
         std::cout << "Invalid OP code\n";
         break;
   }
}

/**
 * ============================================================================
 *
 * @name       op_alu_shift
 *
 * @brief      Shift VY left or right 1 bit and store in VX
 *             OPCODE 8XY6: Store the value of register VY shifted right one bit in register VX
 *                          Set register VF to the least significant bit prior to the shift
 *                          VY is unchanged
 *             OPCODE 8XYE: Store the value of register VY shifted left one bit in register VX??
 *                          Set register VF to the most significant bit prior to the shift
 *                          VY is unchanged
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_alu_shift(opcode_t opcode, CPU *cpu)
{
   reg_index_t reg_x_index = GET_NIBBLE_2(opcode);
   reg_index_t reg_y_index = GET_NIBBLE_1(opcode);
   reg_val_t   reg_y       = cpu->get_reg(reg_y_index);

   switch(GET_NIBBLE_0(opcode))
   {
      case ALU_SHIFT_RIGHT:
         cpu->set_reg(VFLAG, reg_y & LSB_BIT_MASK);
         cpu->set_reg(reg_x_index, reg_y >> 1);
         break;

      case ALU_SHIFT_LEFT:
         cpu->set_reg(VFLAG, reg_y & MSB_BIT_MASK);
         cpu->set_reg(reg_x_index, reg_y << 1);
         break;

      default:
         std::cout << "Invalid OP code\n";
         break;
   }
}

static void (*opcode_alu_table[NUM_OF_ALU_OPCODES])(uint16_t, CPU*) =
{
   op_alu_store,   op_alu_bitwise, op_alu_bitwise,
   op_alu_bitwise, op_alu_add_sub, op_alu_add_sub,
   op_alu_shift,   op_alu_add_sub, op_alu_shift
};

/**
 * ============================================================================
 *
 * @name       op_alu
 *
 * @brief      OPCODE 8XXX
 *             Various ALU related operations
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_alu(opcode_t opcode, CPU *cpu)
{
   opcode_t opcode_alu_entry = GET_NIBBLE_0(opcode);
   (opcode_alu_entry == ALU_SHIFT_LEFT) ? opcode_alu_table[OP_8XXE](opcode, cpu) :
                                          opcode_alu_table[opcode_alu_entry](opcode, cpu);
}

/**
 * ============================================================================
 *
 * @name       op_random
 *
 * @brief      OPCODE CXNN
 *             Set VX to a random number with a mask of NN
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
static void op_random(opcode_t opcode, CPU *cpu)
{
   std::srand(std::time(nullptr));
   int random_byte_val = std::rand() % MAX_BYTE_VAL;

   cpu->set_reg(GET_NIBBLE_2(opcode), (random_byte_val & GET_BYTE_0(opcode)));
}

static void (*opcode_table[NUM_OF_OPCODES])(uint16_t, CPU*) =
{
   op_sys_calls, op_jump,    op_subroutine, op_compare,
   op_compare,   op_compare, op_store,      op_add,
   op_alu,       op_compare, op_store,      op_jump,
   op_random,    op_null,    op_null,       op_null
};


/**
 * ============================================================================
 *
 * @name       execute_opcode
 *
 * @brief      Execute an opcode instruction
 *
 * @param[in]  opcode_t opcode - The opcode being used
 * @param[in]  CPU*     cpu    - Pointer to main CPU object
 *
 * @return    void
 *
 * ============================================================================
*/
rc_e execute_opcode(opcode_t opcode, CPU *cpu)
{
   rc_e     rc           = SUCCESS;
   opcode_t opcode_entry = 0;

   opcode_entry = GET_NIBBLE_3(opcode);
   opcode_table[opcode_entry](opcode, cpu);

   return rc;
}
