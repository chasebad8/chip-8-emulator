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

/* Memory, CHIP-8 Doesn't use ROM, everything is
   writable in this interpreter */
#define RAM_MAX_BYTES   4095
typedef uint8_t ram_t[RAM_MAX_BYTES];

/* 16 CPU registers of size 1 byte */
#define CPU_REGS_MAX   17
typedef uint8_t reg_t[CPU_REGS_MAX];

/* 2 byte PC reg, holds current memory address */
typedef uint16_t pc_t;

/* CPU registers V0 through F */
typedef enum cpu_regs_e
{
   V0 = 0,
   V1,
   V2,
   V3,
   V4,
   V5,
   V6,
   V7,
   V8,
   V9,
   VA,
   VB,
   VC,
   VD,
   VE,
   VF,
   VFLAG = VF,

   MAX_CPU_REG

} cpu_regs_e;

class CPU
{
   private:
      pc_t    pc;
      reg_t   reg;
      ram_t   ram;

   public:
      CPU();

      rc_e set_reg(cpu_regs_e, uint8_t);
      rc_e get_reg(cpu_regs_e, uint8_t*);

      rc_e set_pc(uint16_t);
      rc_e get_pc(uint16_t*);

      rc_e fetch();
      rc_e decode_execute();
};

#ifdef __cplusplus
}
#endif

#endif /* __CPU_H__ */