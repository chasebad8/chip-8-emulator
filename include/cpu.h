/******************************************************************************
  * @file           : cpu.h
  * @brief          : core definitions for chip-8 CPU
  ******************************************************************************
  * @attention
  *
  * @author Chase B
  * @date   2023/03/09
  *
  ******************************************************************************
*/

#ifndef __CPU_H__
#define __CPU_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum opcodes
{
   OP_00E0,
   OP_00EE,
   OP_0NNN,
   OP_1NNN,
   OP_2NNN,
   OP_3XNN,
   OP_4XNN,
   OP_5XY0,
   OP_6XNN,
   OP_7XNN,
   OP_8XY0,
   OP_8XY1,
   OP_8XY2,
   OP_8XY3,
   OP_8XY4,
   OP_8XY5,
   OP_8XY6,
   OP_8XY7,
   OP_8XYE,
   OP_9XY0,
   OP_ANNN,
   OP_BNNN,
   OP_CXNN,
   OP_DXYN,
   OP_EX9E,
   OP_EXA1,
   OP_FX07,
   OP_FX0A,
   OP_FX15,
   OP_FX18,
   OP_FX1E,
   OP_FX29,
   OP_FX33,
   OP_FX55,
   OP_FX65,

   NUM_OF_OPCODES = OP_FX65

} opcodes;

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
class CPU
{
   private:

   public:
      rc_e fetch();
      rc_e decode();
      rc_e execute();
}
