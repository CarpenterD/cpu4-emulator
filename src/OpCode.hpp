#ifndef OPCODE
#define OPCODE

// CPU 4 OpCodes and specification can be found at
// https://robotics.ee.uwa.edu.au/courses/embedded/tutorials/tutorials/tutorial_2/T2_second_page.htm

enum class OpCode : unsigned char {
    LOAD_M = 0,
    STORE  = 1,
    NOT    = 2,
    ADD_M  = 3,
    SUB_M  = 4,
    AND_M  = 5,
    OR_M   = 6,
    BEQ    = 7,
    LOAD_I = 8,
    //UNUSED  9
    //UNUSED 10
    ADD_I  = 11,
    SUB_I  = 12,
    AND_I  = 13,
    OR_I   = 14,
    BRA    = 15,
};

#endif
