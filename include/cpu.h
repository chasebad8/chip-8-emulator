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

#include "opcodes.h"
#include "common_types.h"

class CPU
{
   private:
      OPCODES opcodes;
   public:
      rc_e fetch();
      rc_e decode();
      rc_e execute();
};

#ifdef __cplusplus
}
#endif

#endif /* __CPU_H__ */