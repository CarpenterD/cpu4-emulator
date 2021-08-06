#ifndef CPU_4
#define CPU_4

#include <ostream>

#define MEMORY_SIZE 256

namespace emulator{
    class CPU4
    {
        private:
            unsigned char PC;
            unsigned char ACCU;
            unsigned char Code;
            unsigned char Address;
            unsigned int  Clock;
            unsigned char *Mem;

            void Step();

        public:
            CPU4(unsigned char *memory);

            void Run(unsigned int cycles);
            unsigned char* GetMemory();

            friend std::ostream& operator<< (std::ostream& stream, const CPU4& cpu);
    };

    std::ostream& operator<< (std::ostream& stream, const CPU4& matrix);
}

#endif
