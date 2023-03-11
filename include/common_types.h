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

#define GET_FIRST_NIBBLE(opcode)((opcode & 0xF000) >> 12)
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