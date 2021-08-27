#ifndef TOKEN
#define TOKEN

#include <string>

namespace asm4
{
    struct Token
    {
        public:
            Token(std::string text, int column, int row);

            std::string Text;
            int Col;
            int Row;
    };
}

#endif