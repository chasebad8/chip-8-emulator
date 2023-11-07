# Overview
An emulator for the chip-8 interpreter. The goal of this project was to get familiar with emulation and refresh my knowledge of object oriented programming/C++.

# Links
https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Instruction-Set
https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Technical-Reference
https://github.com/corax89/chip8-test-rom/blob/master/README.md

# Demonstration
Below is an example of my emulator running a Rock Paper Scissors ROM by SystemLogoff from the OctoJam event.

https://github.com/chasebad8/chip-8-emulator/assets/51832821/35bd8b61-e1f6-47c4-8dfb-1d1bc60a7759

# Comments
Initially I wanted to use function pointers such that most of the opcodes could be called using as few specific API's as possible. Unfortunately I pass in a generic opcode as the argument into my function pointer array. This means that inside each implemented function I had to decode what registers I needed to write on based on the sub-code. Next time I think passing in the registers / values to manipulate would allow for much less sub-code handling.

