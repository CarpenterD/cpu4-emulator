#include "Lexer.hpp"
#include "Token.hpp"

#include <iostream>

#define COMMENT_DELIMITER '#'

namespace
{
    
}

asm4::Token::Token(std::string text, int column, int row) 
: Col{column}, Row{row}
{
    Text = text;
}