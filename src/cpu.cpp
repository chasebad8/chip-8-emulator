#include <iostream>
#include "cpu.h"
#include "opcodes.h"

#define MEM_READ_2_BYTES 2

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
rc_e CPU::set_i_reg(i_reg_val_t value)
{
   i_reg = value;
   return SUCCESS;
}

/**
 * ============================================================================
 *
 * @name       set_i_reg_plus_offset
 *
 * @brief      add an offset to current i reg value
 *
 * @param[in] value - the memory location to set PC to
 *
 * @return    rc_e
 *
 * ============================================================================
*/
rc_e CPU::set_i_reg_plus_offset(reg_val_t value)
{
   i_reg = i_reg + value;
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
i_reg_val_t CPU::get_i_reg()
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
rc_e CPU::mem_stack_push(pc_t mem_val)
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
 * @return    pc_t
 *
 * ============================================================================
*/
pc_t CPU::mem_stack_top()
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
 * @return     rc_e
 *
 * ============================================================================
*/
rc_e CPU::set_mem(mem_index_t mem_index, mem_val_t mem_value)
{
   mem[mem_index] = mem_value;
   return SUCCESS;
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
 * @name       set_timer
 *
 * @brief      set the value of the timer register
 *
 * @param[in] value - the memory location to set PC to
 *
 * @return    rc_e
 *
 * ============================================================================
*/
rc_e CPU::set_timer(timer_val_t value)
{
   timer = value;
   return SUCCESS;
}

/**
 * ============================================================================
 *
 * @name       update_timer
 *
 * @brief      update the value of the timer register
 *
 * @return    rc_e
 *
 * ============================================================================
*/
rc_e CPU::update_timer()
{
   timer --;
   return SUCCESS;
}



/**
 * ============================================================================
 *
 * @name       get_timer
 *
 * @brief      get the current value of the delay timer register
 *  *
 * @return    timer_value_t
 *
 * ============================================================================
*/
timer_val_t CPU::get_timer()
{
   return timer;
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
   logger->info("Fetched opcode: {0:X}", opcode);
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
   SDL_Event event;
   uint32_t  reference_tick = 0;
   uint32_t  frame_rate     = 0;
   bool      running        = true;
   opcode_t  opcode         = 0x0000;

   /* Check if mem is empty / null */
   do
   {
      std::cout << "" << std::endl;
      logger->info("PC: {0:X}", pc);

      reference_tick = SDL_GetTicks();

      opcode = fetch();

      /* Probably should do some opcode validation here*/
      if(decode_execute(opcode) != SUCCESS)
      {
         logger->error("Failed to debug or execute opcode");
      }
      else if(update_display == true)
      {
         gpu_update_display(pixel_map);
      }

      /* Throttle emulator execution so we run at 60Hz */
      /* (TODO: This doesn't actually throttle to 60Hz) */
      if((frame_rate = SDL_GetTicks() - reference_tick) < MS_PER_CLK_CYCLE)
      {
         SDL_Delay(MS_PER_CLK_CYCLE - frame_rate);
      }

      /* If user clicks close window, exit program */
      while (SDL_PollEvent(&event))
      {
         if (event.type == SDL_QUIT)
         {
            running = false;
            logger->info("Chip-8 Shutting Down");
         }
      }

      if(timer > 0)
      {
         update_timer();
      }

      /* Each reg is 1 byte and we just read 2 */
      set_pc(pc + MEM_READ_2_BYTES);

   } while((running == true));

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
CPU::CPU(const char* rom_path)
{
   logger = spdlog::get("main");
   logger->info("Initializing CPU ...");

   update_display = false;
   pc             = INSTRUCTION_ADDRESS_START;

   /* Clear memory */
   std::fill(std::begin(mem), std::end(mem), 0x00);

   /* Clear CPU Registers */
   std::fill(std::begin(reg), std::end(reg), 0x00);

   /* Clear GPU Pixel map */
   memset(pixel_map, 0, sizeof(pixel_map));

   /* Load the 9 number sprites into memory starting at address 0x000 */
   for(int i = 0; i < NUM_FONTS; i++)
   {
      mem[i] = font[i];
   }

   /* Copy ROM to memory starting at address 0x200 */
   logger->info("Copying ROM ({:s}) to memory ...", rom_path);
   FILE* game = fopen(rom_path, "rb");
   if (!game) {
      logger->error("Unable to open file");
   }
   else
   {
      fread(&mem[INSTRUCTION_ADDRESS_START], 1, MEMORY_MAX_BYTES - INSTRUCTION_ADDRESS_START, game);
      fclose(game);
      logger->info("Copy ROM to memory complete!");
   }

   /* Draw a few random dots (TODO: Remove this) */
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