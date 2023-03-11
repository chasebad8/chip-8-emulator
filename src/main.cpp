#include <iostream>
#include "cpu.h"

int main() {
   std::cout << "Booting up CHIP-8 ...\n";
   CPU cpu;
   cpu.decode_execute();

   return 0;
}