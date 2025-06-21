#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

// トークンの種類
enum class TokenType {
    DOUBLE, PLUS, MINUS, MUL, DIV,
    LPAREN, RPAREN, LBRACE, RBRACE,
    VAR, IF, ELSE, WHILE, // <-- WHILE を追加
    TRUE, FALSE,
    ID, ASSIGN, EQ, NEQ, LT, GT, LTE, GTE,
    SEMI, END_OF_FILE
};

// トークンを表す構造体
struct Token {
    TokenType type;
    double value {0.0};
    std::string name;

    // トークンをデバッグ用に文字列に変換する
    std::string to_string() const;
};

#endif // TOKEN_H
