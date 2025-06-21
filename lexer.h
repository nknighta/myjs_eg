#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>
#include <unordered_map>

class Lexer {
public:
    Lexer(std::string text);
    Token get_next_token();

private:
    std::string text_;
    size_t pos_;
    std::unordered_map<std::string, Token> reserved_keywords;

    char peek();
    Token number();
    Token identifier();
};

#endif // LEXER_H
