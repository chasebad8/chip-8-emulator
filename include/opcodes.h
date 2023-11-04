/******************************************************************************
  * @file           : OPCODES.h
  * @brief          : core definitions for chip-8 CPU
  ******************************************************************************
  * @attention
  *
  * @author Chase B
  * @date   2023/03/09
  *
  ******************************************************************************
*/

#ifndef __OPCODES_H__
#define __OPCODES_H__

#include <cstdint>
#include "common_types.h"
#include "cpu.h"

#define VFLAG_CLEAR       0
#define VFLAG_CARRY       1
#define VFLAG_BORROW      0
#define VFLAG_NO_BORROW   1

#define LSB_BIT_MASK      0x01
#define MSB_BIT_MASK      0x80

#define REGISTER_0        0

typedef enum opcodes_e
{
   OP_0XXX,
   OP_1XXX,
   OP_2XXX,
   OP_3XXX,
   OP_4XXX,
   OP_5XXX,
   OP_6XXX,
   OP_7XXX,
   OP_8XXX,
   OP_9XXX,
   OP_AXXX,
   OP_BXXX,
   OP_CXXX,
   OP_DXXX,
   OP_EXXX,
   OP_FXXX,

   NUM_OF_OPCODES
} opcodes_e;

typedef enum opcodes_alu_e
{
   OP_8XX0,
   OP_8XX1,
   OP_8XX2,
   OP_8XX3,
   OP_8XX4,
   OP_8XX5,
   OP_8XX6,
   OP_8XX7,
   OP_8XXE,

   NUM_OF_ALU_OPCODES
} opcodes_alu_e;

typedef enum opcodes_0xxx_e
{
  CLEAR  = 0xE0,
  RETURN = 0xEE
} opcodes_0xxx_e;

typedef enum opcodes_compare_e
{
  EQUAL         = 3,
  NOT_EQUAL     = 4,
  EQUAL_REG     = 5,
  NOT_EQUAL_REG = 9

} opcodes_compare_e;

typedef enum alu_operations_e
{
  ALU_OR  = 1,
  ALU_AND = 2,
  ALU_XOR = 3,

  ALU_ADD = 4,
  ALU_SUB,

  ALU_SHIFT_RIGHT,
  ALU_STORE,
  ALU_SHIFT_LEFT = 14

} alu_operations_e;

typedef enum opcodes_8xxx_e
{
  OP_8XY0,
  OP_8XY1,
  OP_8XY2,
  OP_8XY3,
  OP_8XY4,
  OP_8XY5,
  OP_8XY6,
  OP_8XY7,
  OP_8XYE,

  NUM_OF_OPCODES_8XXX
} opcodes_8xxx_e;

typedef enum opcodes_skip_e
{
  SKIP_IS_PRESSED = 0x9E,
  SKIP_NOT_PRESSED = 0xA1,

} opcodes_skip_e;

typedef enum opcodes_exxx_e
{
  MISC_STORE_DELAY       = 0x07,
  MISC_WAIT_FOR_KEYPRESS = 0x0A,
  MISC_SET_DELAY         = 0x15,
  MISC_SET_SOUND         = 0x18,
  MISC_ADD_VX_I          = 0x1E,
  MISC_SET_I_VX          = 0x29,
  MISC_BCD               = 0x33,
  MISC_STORE_REG         = 0x55,
  MISC_FILL_REG          = 0x65,

} opcodes_exxx_e;

/*
0xxx: These opcodes are either used for system calls, or to manipulate the display.
1xxx: This opcode is used for an unconditional jump to a specific address.
2xxx: This opcode is used to call a subroutine at a specific address.
3xxx: This opcode is used to skip the next instruction if a specific register is equal to a specific value.
4xxx: This opcode is used to skip the next instruction if a specific register is not equal to a specific value.
5xxx: This opcode is used to skip the next instruction if two specific registers are equal to each other.
6xxx: This opcode is used to load a specific value into a specific register.
7xxx: This opcode is used to add a specific value to a specific register.
8xxx: This opcode is used for a variety of register-to-register operations.
9xxx: This opcode is used to skip the next instruction if two specific registers are not equal to each other.
Axxx: This opcode is used to set the value of the address register to a specific value.
Bxxx: This opcode is used to jump to a specific address plus the value of register 0.
Cxxx: This opcode is used to set a specific register to a random value and a specific value.
Dxxx: This opcode is used to draw a sprite to the screen.
Ex9E: This opcode is used to skip the next instruction if a specific key is currently pressed.
ExA1: This opcode is used to skip the next instruction if a specific key is currently not pressed.
Fxxx: This opcode is used for a variety of operations, such as setting a register to the value of the delay timer,
      waiting for a key press, or adding a specific register to the address register.
*/

/* Deprecated. Bad to use bit fields for endianness */
typedef struct opcode_s
{
   uint16_t opcode;

   union
   {
      uint8_t byte_0;
      uint8_t byte_1;
   };
   union
   {
      uint16_t nibble_0 : 4;
      uint16_t nibble_1 : 4;
      uint16_t nibble_2 : 4;
      uint16_t nibble_3 : 4;
   };
   union
   {
    uint16_t nibble_byte : 12;
    uint16_t unused      : 4;
   };

} opcode_s;

/**
 * ============================================================================
 *
 * @name       init_log_opcodes
 *
 * @brief      Initialize the log for opcode static functions
 *
 * @return     void
 *
 * ============================================================================
*/
void init_log_opcodes();

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
rc_e execute_opcode(uint16_t opcode, CPU *cpu);

#endif /* __OPCODES_H__ */