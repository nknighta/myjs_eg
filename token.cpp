#include "token.h"

// トークンをデバッグ用に文字列に変換する
std::string Token::to_string() const {
    switch (type) {
        case TokenType::DOUBLE:  return "DOUBLE(" + std::to_string(value) + ")";
        case TokenType::PLUS:    return "PLUS";
        case TokenType::MINUS:   return "MINUS";
        case TokenType::MUL:     return "MUL";
        case TokenType::DIV:     return "DIV";
        case TokenType::LPAREN:  return "LPAREN";
        case TokenType::RPAREN:  return "RPAREN";
        case TokenType::LBRACE:  return "LBRACE";
        case TokenType::RBRACE:  return "RBRACE";
        case TokenType::VAR:     return "VAR";
        case TokenType::IF:      return "IF";
        case TokenType::ELSE:    return "ELSE";
        case TokenType::WHILE:   return "WHILE"; // <-- WHILE を追加
        case TokenType::TRUE:    return "TRUE";
        case TokenType::FALSE:   return "FALSE";
        case TokenType::ID:      return "ID(" + name + ")";
        case TokenType::ASSIGN:  return "ASSIGN";
        case TokenType::EQ:      return "EQ";
        case TokenType::NEQ:     return "NEQ";
        case TokenType::LT:      return "LT";
        case TokenType::GT:      return "GT";
        case TokenType::LTE:     return "LTE";
        case TokenType::GTE:     return "GTE";
        case TokenType::SEMI:    return "SEMI";
        case TokenType::END_OF_FILE: return "EOF";
        default: return "UNKNOWN";
    }
}