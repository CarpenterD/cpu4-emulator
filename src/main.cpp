#include <iostream>

#include "op-codes.hpp"
#include "CPU4.hpp"

int main(int argc, char *argv[]){

    unsigned char mem[MEMORY_SIZE];
    for (size_t i = 0; i < MEMORY_SIZE; i++)
    {
        mem[i] = 0;
    }

    // Sample hardcoded instructions
    mem[0] = 0; //LOAD_M
    mem[1] = 0x01;
    mem[2] = 11; //ADD_I
    mem[3] = 0x01;
    mem[4] = 1; //STORE
    mem[5] = 0x10;
    mem[6] = 15; //BRA
    mem[7] = 0xFE; // -2
    
    emulator::CPU4 cpu(mem);
    cpu.Run(5);
    std::cout << cpu << std::endl;

    return EXIT_SUCCESS;
}
