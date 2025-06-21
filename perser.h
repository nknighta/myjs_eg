#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"
#include <memory>

class Parser {
public:
    Parser(Lexer& lexer);
    std::unique_ptr<ASTNode> parse();

private:
    Lexer& lexer_;
    Token current_token_;

    void eat(TokenType type);

    // Grammar Rules
    std::unique_ptr<ASTNode> program();
    std::unique_ptr<ASTNode> statement_list();
    std::unique_ptr<ASTNode> statement();
    std::unique_ptr<ASTNode> block();
    std::unique_ptr<ASTNode> if_statement();
    std::unique_ptr<ASTNode> variable_declaration();
    std::unique_ptr<ASTNode> expression();
    std::unique_ptr<ASTNode> arith_expr();
    std::unique_ptr<ASTNode> term();
    std::unique_ptr<ASTNode> factor();
};

#endif // PARSER_H
