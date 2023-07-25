#include <iostream>
#include "gpu.h"
#include "cpu.h"
#include "opcodes.h"

#define MEM_READ_2_BYTES   2

/**
 * ============================================================================
 *
 * @name       set_reg
 *
 * @brief      Set a CPU register value
 *
 * @param[in]  reg_index - index of the CPU registers
 * @param[in]  value - the value to write into the CPU reg
 *
 * @return    void
 *
 * ============================================================================
*/
rc_e CPU::set_reg(reg_index_t reg_index, uint8_t value)
{
   reg[reg_index] = value;
   return SUCCESS;
}

/**
 * ============================================================================
 *
 * @name       get_reg
 *
 * @brief      get a CPU register value
 *
 * @param[in]  reg_index - index of the CPU registers
 *
 *
 * @return    reg_val_t
 *
 * ============================================================================
*/
reg_val_t CPU::get_reg(reg_index_t reg_index)
{
   return reg[reg_index];
}

/**
 * ============================================================================
 *
 * @name       set_i_reg
 *
 * @brief      set the current memory value in I reg
 *
 * @param[in] value - the memory location to set I reg to
 *
 * @return    rc_e
 *
 * ============================================================================
*/
rc_e CPU::set_i_reg(mem_val_t value)
{
   i_reg = value;
   return SUCCESS;
}

/**
 * ============================================================================
 *
 * @name       get_i_reg
 *
 * @brief      get the current memory location stored in I reg
 *  *
 * @return    pc_val_t
 *
 * ============================================================================
*/
mem_val_t CPU::get_i_reg()
{
   return i_reg;
}

/**
 * ============================================================================
 *
 * @name       mem_stack_push
 *
 * @brief      Push the inputted argument on to the stack
 *
 * @param[in] mem_val - the memory location to put on the stack
 *
 * @return    rc_e
 *
 * ============================================================================
*/
rc_e CPU::mem_stack_push(mem_val_t mem_val)
{
   mem_stack.push(mem_val);
   return SUCCESS;
}

/**
 * ============================================================================
 *
 * @name       mem_stack_pop
 *
 * @brief      Pop the top value off of the stack
 *  *
 * @return    rc_e
 *
 * ============================================================================
*/
rc_e CPU::mem_stack_pop()
{
   mem_stack.pop();
   return SUCCESS;
}

/**
 * ============================================================================
 *
 * @name       mem_stack_top
 *
 * @brief      get the top value from the stack
 *  *
 * @return    mem_val_t
 *
 * ============================================================================
*/
mem_val_t CPU::mem_stack_top()
{
   return mem_stack.top();
}

/**
 * ============================================================================
 *
 * @name       set_pc
 *
 * @brief      set the current location of the program counter
 *
 * @param[in] value - the memory location to set PC to
 *
 * @return    rc_e
 *
 * ============================================================================
*/
rc_e CPU::set_pc(uint16_t value)
{
   pc = value;
   return SUCCESS;
}

/**
 * ============================================================================
 *
 * @name       set_pc_plus_offset
 *
 * @brief      skip 1 instruction
 *
 * @param[in] value - the memory location to set PC to
 *
 * @return    rc_e
 *
 * ============================================================================
*/
rc_e CPU::set_pc_plus_offset(uint16_t value)
{
   pc = pc + value;
   return SUCCESS;
}

/**
 * ============================================================================
 *
 * @name       get_pc
 *
 * @brief      get the current location of the program counter
 *  *
 * @return    pc_val_t
 *
 * ============================================================================
*/
pc_val_t CPU::get_pc()
{
   return pc;
}

/**
 * ============================================================================
 *
 * @name       get_mem
 *
 * @brief      get the 8 bit value in the memory register mem_index
 *
 * @param[in]  reg_index - index of the CPU registers
 *
 * @return     mem_val_t
 *
 * ============================================================================
*/
mem_val_t CPU::get_mem(mem_index_t mem_index)
{
   return mem[mem_index];
}

/**
 * ============================================================================
 *
 * @name      fetch
 *
 * @brief     fetch an instruction from memory
 *
 * @return    rc_e
 *
 * ============================================================================
*/
opcode_t CPU::fetch()
{
   logger->info("Fetching instruction");
   return ((get_mem(pc) << 8) | get_mem(pc + 1));
}

/**
 * ============================================================================
 *
 * @name       decode_execute
 *
 * @brief      decode and execute an opcode instruction
 *
 * @param[out] value - the memory location inside PC
 *
 * @return    rc_e
 *
 * ============================================================================
*/
rc_e CPU::decode_execute(opcode_t opcode)
{
   logger->info("Received opcode: {0:X}", opcode);
   execute_opcode(opcode, this);

   return SUCCESS;
}

/**
 * ============================================================================
 *
 * @name       set_pixel_map
 *
 * @brief      set the CPU's pixel map
 *
 * @param[in]  x - x coord of pixel map
 * @param[in]  y - y coord of pixel map
 * @param[in]  value - the memory location inside PC
 *
 * @return    rc_e
 *
 * ============================================================================
*/
rc_e CPU::set_pixel_map(uint8_t x, uint8_t y, uint32_t value)
{
   pixel_map[x][y] = value;
   return SUCCESS;
}

/**
 * ============================================================================
 *
 * @name       get_pixel_map
 *
 * @brief      get the CPU's pixel map
 *
 * @param[in]  x - x coord of pixel map
 * @param[in]  y - y coord of pixel map
 *
 * @return    uint32_t
 *
 * ============================================================================
*/
uint32_t CPU::get_pixel_map(uint8_t x, uint8_t y)
{
   return pixel_map[x][y];
}
/**
 * ============================================================================
 *
 * @name       clear_pixel_map
 *
 * @brief      clear the pixel map
 *
 * @return     void
 *
 * ============================================================================
*/
void CPU::clear_pixel_map()
{
   memset(pixel_map, 0, sizeof(pixel_map));
}

/**
 * ============================================================================
 *
 * @name       run
 *
 * @brief      main loop that runs chip-8 program
 *
 * @return     rc_e
 *
 * ============================================================================
*/
rc_e CPU::run()
{
   /* Check if mem is empty / null */
   for(int i = 0; i < 10; i ++)
   {
      opcode_t opcode = fetch();

      /* Probably should do some opcode validation here*/
      decode_execute(opcode);

      if(update_display == true)
      {
         gpu_update_display(pixel_map);
      }

      /* Each reg is 1 byte and we just read 2 */
      set_pc(pc + MEM_READ_2_BYTES);

      SDL_Delay(1000);
   }

   gpu_shutdown();

   return SUCCESS;
}

/**
 * ============================================================================
 *
 * @name       CPU
 *
 * @brief      No argument constructor for the CPU class
 *  *
 * @return    none
 *
 * ============================================================================
*/
CPU::CPU()
{
   logger = spdlog::get("main");
   logger->info("Initializing CPU ...");

   /* Initially set all RAM to 0 */
   std::fill(std::begin(mem), std::end(mem), 0x00);
   std::fill(std::begin(reg), std::end(reg), 0x00);
   memset(pixel_map, 0, sizeof(pixel_map));

   update_display = false;
   pc = 0;

   // mem[0] = 0xba;
   // mem[1] = 0xcc;

   mem[100] = 0xF0;
   mem[101] = 0x90;
   mem[102] = 0xF0;
   mem[103] = 0x90;
   mem[104] = 0xF0;

   mem[105] = 0xF0;
   mem[106] = 0x90;
   mem[107] = 0x90;
   mem[108] = 0x90;
   mem[109] = 0xF0;

   /* Store addy 8 into I reg */
   mem[0] = 0xA0;
   mem[1] = 0x64;

   /* Print 8 */
   mem[2] = 0xDA;
   mem[3] = 0xA5;

   /* Store addy 0 into I reg */
   mem[4] = 0xA0;
   mem[5] = 0x69;

   /* Print 0 */
   mem[6] = 0xDF;
   mem[7] = 0xFF;

   /* clear */
   mem[8] = 0x00;
   mem[9] = 0xE0;

   SDL_Delay(1000);

   pixel_map[32][16] = 1;
   pixel_map[50][3]  = 1;

   gpu_update_display(pixel_map);
   SDL_Delay(1000);

   pixel_map[1][30] = 1;
   pixel_map[50][3] = 0;

   gpu_update_display(pixel_map);
   SDL_Delay(1000);

   pixel_map[32][16] = 0;
   pixel_map[50][3]  = 0;
   pixel_map[1][30]  = 0;
   pixel_map[50][3]  = 0;

   gpu_update_display(pixel_map);
   SDL_Delay(1000);

}