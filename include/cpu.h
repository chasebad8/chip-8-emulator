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

#include <stack>
#include <cstdint>
#include "common_types.h"
#include "spdlog/spdlog.h"

/* Memory, CHIP-8 has 4095 memory addresses which
   means that its range is 12 bit addressable. */
#define MEMORY_MAX_BYTES          4095
#define INSTRUCTION_ADDRESS_START 512
#define NUM_FONTS                 80
typedef uint8_t  mem_t[MEMORY_MAX_BYTES];
typedef uint16_t mem_index_t;
typedef uint8_t  mem_val_t;

/* The font map, to be stored in memory */
static const uint8_t font[NUM_FONTS] = {
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

/* 16 CPU registers of size 1 byte */
#define CPU_MAX_REGS   16
typedef uint8_t  reg_t[CPU_MAX_REGS];
typedef uint16_t reg_index_t;
typedef uint8_t  reg_val_t;

/* The I reg holds a 12 bit address value */
typedef uint16_t i_reg_val_t;

/* 2 byte PC reg, holds current memory address */
typedef uint16_t pc_t;
typedef uint16_t pc_val_t;

class CPU
{
   private:
      std::stack<mem_val_t> mem_stack;
      i_reg_val_t           i_reg;
      pc_t                  pc;
      reg_t                 reg;
      mem_t                 mem;
      pixel_map_t           pixel_map;
      std::shared_ptr<spdlog::logger> logger;

   public:
      CPU();

      rc_e      set_pixel_map(uint8_t x, uint8_t y, uint32_t value);
      uint32_t  get_pixel_map(uint8_t x, uint8_t y);
      void      clear_pixel_map();
      bool      update_display;

      rc_e      mem_stack_push(mem_val_t);
      rc_e      mem_stack_pop();
      mem_val_t mem_stack_top();

      rc_e        set_i_reg(i_reg_val_t);
      i_reg_val_t get_i_reg();

      rc_e      set_reg(reg_index_t, reg_val_t);
      reg_val_t get_reg(reg_index_t);

      rc_e     set_pc(pc_val_t);
      rc_e     set_pc_plus_offset(pc_val_t);
      pc_val_t get_pc();

      mem_val_t get_mem(mem_index_t);

      opcode_t fetch();
      rc_e decode_execute(opcode_t);

      rc_e run();
};

#endif /* __CPU_H__ */