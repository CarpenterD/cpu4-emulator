#ifndef TOKEN
#define TOKEN

#include <string>

namespace asm4
{
    struct Token
    {
        public:
            std::string Token;
            int Col;
            int Row;
    };
}

#endif