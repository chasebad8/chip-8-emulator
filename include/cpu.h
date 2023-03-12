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

#include "common_types.h"

/* Memory, CHIP-8 has 4095 memory addresses which
   means that its range is 12 bit addressable. */
#define MEMORY_MAX_BYTES   4095
typedef uint8_t  mem_t[MEMORY_MAX_BYTES];
typedef uint16_t mem_index_t;
typedef uint8_t  mem_val_t;

/* 16 CPU registers of size 1 byte */
#define CPU_MAX_REGS   17
typedef uint8_t  reg_t[CPU_MAX_REGS];
typedef uint16_t reg_index_t;
typedef uint8_t  reg_val_t;

/* 2 byte PC reg, holds current memory address */
typedef uint16_t pc_t;
typedef uint16_t pc_val_t;

class CPU
{
   private:
      pc_t    pc;
      reg_t   reg;
      mem_t   mem;

   public:
      CPU();

      rc_e set_reg(reg_index_t, reg_val_t);
      reg_val_t get_reg(reg_index_t);

      rc_e set_pc(pc_val_t);
      rc_e set_pc_plus_offset(pc_val_t);
      pc_val_t get_pc();

      mem_val_t get_mem(mem_index_t);

      rc_e fetch();
      rc_e decode_execute();
};

#ifdef __cplusplus
}
#endif

#endif /* __CPU_H__ */