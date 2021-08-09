#ifndef LEXER
#define LEXER

#include <vector>

#include "Token.hpp"

namespace asm4
{
    namespace lex
    {
        std::vector<Token> GetTokens(std::string text);
    }
}

#endif
