#include "lexer.h"
#include <stdexcept>
#include <cctype>

Lexer::Lexer(std::string text) : text_(std::move(text)), pos_(0) {
    reserved_keywords["var"] = Token{TokenType::VAR};
    reserved_keywords["if"] = Token{TokenType::IF};
    reserved_keywords["else"] = Token{TokenType::ELSE};
    reserved_keywords["true"] = Token{TokenType::TRUE, 1.0};
    reserved_keywords["false"] = Token{TokenType::FALSE, 0.0};
}

char Lexer::peek() {
    if (pos_ + 1 >= text_.length()) return '\0';
    return text_[pos_ + 1];
}

Token Lexer::get_next_token() {
    while (pos_ < text_.length()) {
        char current_char = text_[pos_];
        if (isspace(current_char)) { pos_++; continue; }
        if (isalpha(current_char) || current_char == '_') { return identifier(); }
        if (isdigit(current_char) || current_char == '.') { return number(); }
        if (current_char == '=' && peek() == '=') { pos_ += 2; return {TokenType::EQ}; }
        if (current_char == '!' && peek() == '=') { pos_ += 2; return {TokenType::NEQ}; }
        if (current_char == '<' && peek() == '=') { pos_ += 2; return {TokenType::LTE}; }
        if (current_char == '>' && peek() == '=') { pos_ += 2; return {TokenType::GTE}; }
        if (current_char == '<') { pos_++; return {TokenType::LT}; }
        if (current_char == '>') { pos_++; return {TokenType::GT}; }
        if (current_char == '=') { pos_++; return {TokenType::ASSIGN}; }
        if (current_char == ';') { pos_++; return {TokenType::SEMI}; }
        if (current_char == '+') { pos_++; return {TokenType::PLUS}; }
        if (current_char == '-') { pos_++; return {TokenType::MINUS}; }
        if (current_char == '*') { pos_++; return {TokenType::MUL}; }
        if (current_char == '/') { pos_++; return {TokenType::DIV}; }
        if (current_char == '(') { pos_++; return {TokenType::LPAREN}; }
        if (current_char == ')') { pos_++; return {TokenType::RPAREN}; }
        if (current_char == '{') { pos_++; return {TokenType::LBRACE}; }
        if (current_char == '}') { pos_++; return {TokenType::RBRACE}; }
        
        throw std::runtime_error("Lexer error: invalid character '" + std::string(1, current_char) + "'");
    }
    return {TokenType::END_OF_FILE};
}

Token Lexer::number() {
    std::string result;
    while (pos_ < text_.length() && (isdigit(text_[pos_]) || text_[pos_] == '.')) {
        result += text_[pos_++];
    }
    return {TokenType::DOUBLE, std::stod(result)};
}

Token Lexer::identifier() {
    std::string result;
    while (pos_ < text_.length() && (isalnum(text_[pos_]) || text_[pos_] == '_')) {
        result += text_[pos_++];
    }
    if (reserved_keywords.count(result)) return reserved_keywords.at(result);
    return {TokenType::ID, 0.0, result};
}
