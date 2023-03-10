#include <iostream>
#include "common_types.h"
#include "cpu.h"

void cpuNULL(uint16_t, uint16_t, uint16_t)
{
	// Do Nothing
}

void (*opcode_table[NUM_OF_OPCODES])(uint16_t, uint16_t, uint16_t) =
{
   cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL,
   cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL,
   cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL,
   cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL,
   cpuNULL, cpuNULL, cpuNULL
};

rc_e CPU::fetch()
{
   return SUCCESS;
}

rc_e CPU::decode()
{
   return SUCCESS;
}

rc_e CPU::execute()
{
   return SUCCESS;
}

int main() {
   std::cout << "Hello World!\n";

   CPU cpu;
   cpu.decode();

   return 0;
}