#include "CPU4.hpp"
#include "OpCode.hpp"

#include <iomanip>

using namespace emulator;

//-----------------------------------------------
// CONSTRUCTOR
//-----------------------------------------------
CPU4::CPU4(unsigned char *memory){
    PC = 0;
    ACCU = 0;
    Code = 0;
    Address = 0;
    Clock = 0;
    Mem = memory;
}



//-----------------------------------------------
// EXECUTION
//-----------------------------------------------
void CPU4::Step(){
    Code = Mem[PC++];
    Address = Mem[PC];

    OpCode op = static_cast<OpCode>(Code & 0b00001111);
    switch (op)
    {
        case OpCode::LOAD_M:
        {
            ACCU = Mem[Address];
            break;
        }
        case OpCode::STORE:
        {
            Mem[Address] = ACCU;
            break;
        }
        case OpCode::NOT:
        {
            ACCU = ~ACCU;
            break;
        }
        case OpCode::ADD_M:
        {
            ACCU += Mem[Address];
            break;
        }
        case OpCode::SUB_M:
        {
            ACCU -= Mem[Address];
            break;
        }
        case OpCode::AND_M:
        {
            ACCU = ACCU & Mem[Address];
            break;
        }
        case OpCode::OR_M:
        {
            ACCU = ACCU | Mem[Address];
            break;
        }
        case OpCode::BEQ:
        {
            if (ACCU = 0) {
                PC += Address;
            }
            break;
        }
        case OpCode::LOAD_I:
        {
            ACCU = Address;
            break;
        }
        case OpCode::ADD_I:
        {
            ACCU += Address;
            break;
        }
        case OpCode::SUB_I:
        {
            ACCU -= Address;
            break;
        }
        case OpCode::AND_I:
        {
            ACCU = ACCU & Address;
            break;
        }
        case OpCode::OR_I:
        {
            ACCU = ACCU | Address;
            break;
        }
        case OpCode::BRA:
        {
            PC += Address;
            break;
        }
        default:
            // TODO
            break;
    }
    PC++;
    Clock++;
}

void CPU4::Run(unsigned int cycles){
    int cyclesDone = 0;
    while (cyclesDone++ < cycles){
        Step();
    }
}

//-----------------------------------------------
// UTILITIES
//-----------------------------------------------
const unsigned char* CPU4::GetMemory(){
    return Mem;
}


#define COLOR_RESET   "\033[0m"
#define COLOR_PC     "\033[93m"
#define COLOR_PC_RAM "\033[1m\033[93m"

namespace emulator{
    std::ostream& operator<<(std::ostream& stream, const CPU4& cpu){
        stream << "Clock: " << std::to_string(cpu.Clock) << std::endl;
        stream << "PC: " << COLOR_PC << std::to_string(cpu.PC) << COLOR_RESET << std::endl;
        stream << "Code: " << std::to_string(cpu.Code) << " Addr: " << std::to_string(cpu.Address) << std::endl;
        stream << "Accumulator = " << std::to_string(cpu.ACCU) << std::endl;
        stream << "Memory:" << std::endl;
        for (size_t i = 0; i < MEMORY_SIZE; i++)
        {
            if (i % 16 == 0){
                stream << std::hex << std::setfill('0') << std::setw(2) << i << " | ";
            }

            if (i == cpu.PC){ stream << COLOR_PC_RAM; }
            stream << std::hex << std::setfill('0') << std::setw(2) << (int) cpu.Mem[i];
            if (i == cpu.PC){ stream << COLOR_RESET; }

            stream << " ";

            if (i % 16 == 15){
                stream << std::endl;
            }
        }
        return stream;
    }
}
