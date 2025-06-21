#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    ILLEGAL,
    END_OF_FILE,

    // タグ
    TAG_START,      // <
    TAG_END,        // >
    TAG_CLOSE,      // </

    // 識別子
    IDENTIFIER,     // タグ名、属性名
    TEXT,           // テキストノード

    // 属性
    ATTRIBUTE_KEY,  // 属性キー
    ATTRIBUTE_VALUE // 属性値
};

struct Token {
    TokenType type;
    std::string literal;
};

#endif // TOKEN_H
