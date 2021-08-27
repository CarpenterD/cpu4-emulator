#include "Lexer.hpp"
#include "Token.hpp"

#include <iostream>

#define COMMENT_DELIMITER '#'



std::vector<asm4::Token> asm4::lex::GetTokens(std::string text) {
    std::vector<asm4::Token> tokens;
    bool inComment = false;
    bool tokCreated = false;

    int tokRow = 0;
    int tokCol = 0;
    std::string tokTxt;
    
    int curRow = 0;
    int curCol = 0;

    std::cout << text << std::endl;

    for (size_t i = 0; i < text.length(); i++)
    {
        char c = text[i];

        if (c == COMMENT_DELIMITER) {
            inComment = true;
        }

        // only add alphanumerics & symbols
        if ( 32 < c && c < 127 ) {
            tokTxt += c;
        }

        if (c==' ' || c=='\t') {
            if (inComment) {
                tokTxt += c;
            } else if (tokTxt.length() > 0) {
                // new token
                tokens.push_back(Token(tokTxt, tokCol, tokRow));
                tokCreated = true;
            }
        }

        if (c == '\n') {
            if (tokTxt.length() > 0) {
                // new token
                if (!inComment){
                    tokens.push_back(Token(tokTxt, tokCol, tokRow));
                }
                tokCreated = true;
            }
            inComment = false;
            curRow++;
            curCol = 0;
        }else{
            curCol++;
        }
        

        if (tokCreated) {
            tokRow = curRow;
            tokCol = curCol;
            tokTxt.clear();
            tokCreated = false;
        }
    }

    // no new line at end of file
    if (tokTxt.length() > 0) {
        tokens.push_back(Token(tokTxt, tokCol, tokRow));
    }

    #ifndef NDEBUG
    
    for (size_t i = 0; i < tokens.size(); i++)
    {
        std::cout << "(" << tokens[i].Row << ":" << tokens[i].Col  << ") " << tokens[i].Text << std::endl;
    }

    #endif
    
    return tokens;
}