/******************************************************************************
  * @file           : common_types.h
  * @brief          : header file that contains common structs and enums
  *                   throughout this project
  ******************************************************************************
  * @attention
  *
  * @author Chase B
  * @date   2023/03/09
  *
  ******************************************************************************
*/

#ifndef __COMMON_TYPES_H__
#define __COMMON_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Grab a specified nibble. Nibble is 4 bits */
#define GET_NIBBLE_0(opcode)(opcode & 0x000F)
#define GET_NIBBLE_1(opcode)((opcode & 0x00F0) >> 4)
#define GET_NIBBLE_2(opcode)((opcode & 0x0F00) >> 8)
#define GET_NIBBLE_3(opcode)((opcode & 0xF000) >> 12)

/* Grab a specified byte. Byte is 8 bits */
#define GET_BYTE_0(opcode)(opcode & 0x00FF)
#define GET_BYTE_1(opcode)((opcode & 0xFF00) >> 8)

/* Grab the first 12 bits. */
#define GET_NIBBLE_BYTE(opcode)(opcode & 0x0FFF)

#define VFLAG 15

typedef enum rc_e
{
  GENERIC_FAIL,
  SUCCESS

} return_code;

typedef enum state_machine_e
{
    POWERED_DOWN = 0,
    BOOT_UP,
    READY,

    /* Running */
    FETCH,
    DECODE,
    EXECUTE,

    /* Failure states */
    EXECUTE_FAIL,
    BAD_OPCODE,
    MEMORY_READ_FAILURE,
    MEMORY_WRITE_FAILURE,

    PAUSE,
    BOOT_DOWN

} state_machine_e;

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_TYPES_H__ */