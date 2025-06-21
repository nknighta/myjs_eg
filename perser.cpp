#include "perser.h"
#include <stdexcept>
#include <stdexcept>

Parser::Parser(Lexer& lexer) : lexer_(lexer) {
    current_token_ = lexer_.get_next_token();
}

void Parser::eat(TokenType type) {
    if (current_token_.type == type) {
        current_token_ = lexer_.get_next_token();
    } else {
        throw std::runtime_error("Parser error: Unexpected token. Expected " + Token{type}.to_string() + " but got " + current_token_.to_string());
    }
}

std::unique_ptr<ASTNode> Parser::parse() {
    return program();
}

std::unique_ptr<ASTNode> Parser::program() {
    auto node = statement_list();
    if (current_token_.type != TokenType::END_OF_FILE) {
        throw std::runtime_error("Parser error: Unexpected token at end of program.");
    }
    return node;
}

std::unique_ptr<ASTNode> Parser::statement_list() {
    auto node = statement();
    auto compound = std::make_unique<CompoundNode>();
    compound->children.push_back(std::move(node));

    while(current_token_.type == TokenType::SEMI) {
        eat(TokenType::SEMI);
        if (current_token_.type == TokenType::RBRACE || current_token_.type == TokenType::END_OF_FILE) break;
        compound->children.push_back(statement());
    }
    
    if (compound->children.size() == 1) return std::move(compound->children[0]);
    return compound;
}

std::unique_ptr<ASTNode> Parser::statement() {
    if (current_token_.type == TokenType::VAR) return variable_declaration();
    if (current_token_.type == TokenType::IF) return if_statement();
    if (current_token_.type == TokenType::LBRACE) return block();
    return expression();
}

std::unique_ptr<ASTNode> Parser::block() {
    eat(TokenType::LBRACE);
    auto node = statement_list();
    eat(TokenType::RBRACE);
    return node;
}

std::unique_ptr<ASTNode> Parser::if_statement() {
    eat(TokenType::IF);
    eat(TokenType::LPAREN);
    auto condition = expression();
    eat(TokenType::RPAREN);
    auto then_branch = statement();
    std::unique_ptr<ASTNode> else_branch = nullptr;
    if (current_token_.type == TokenType::ELSE) {
        eat(TokenType::ELSE);
        else_branch = statement();
    }
    return std::make_unique<IfNode>(std::move(condition), std::move(then_branch), std::move(else_branch));
}

std::unique_ptr<ASTNode> Parser::variable_declaration() {
    eat(TokenType::VAR);
    Token var_token = current_token_;
    eat(TokenType::ID);
    eat(TokenType::ASSIGN);
    auto expr_node = expression();
    return std::make_unique<VarDeclNode>(var_token.name, std::move(expr_node));
}

std::unique_ptr<ASTNode> Parser::factor() {
    Token token = current_token_;
    if (token.type == TokenType::DOUBLE || token.type == TokenType::TRUE || token.type == TokenType::FALSE) {
        eat(token.type);
        return std::make_unique<NumberNode>(token);
    } else if (token.type == TokenType::LPAREN) {
        eat(TokenType::LPAREN);
        auto node = expression();
        eat(TokenType::RPAREN);
        return node;
    } else if (token.type == TokenType::ID) {
        eat(TokenType::ID);
        return std::make_unique<VarNode>(token);
    }
    throw std::runtime_error("Parser error: invalid factor");
}

std::unique_ptr<ASTNode> Parser::term() {
    auto node = factor();
    while (current_token_.type == TokenType::MUL || current_token_.type == TokenType::DIV) {
        Token token = current_token_;
        eat(token.type);
        node = std::make_unique<BinOpNode>(std::move(node), token, factor());
    }
    return node;
}

std::unique_ptr<ASTNode> Parser::arith_expr() {
    auto node = term();
    while (current_token_.type == TokenType::PLUS || current_token_.type == TokenType::MINUS) {
        Token token = current_token_;
        eat(token.type);
        // BUG FIX: The right-hand side of the expression must be a `term` to avoid infinite recursion.
        node = std::make_unique<BinOpNode>(std::move(node), token, term());
    }
    return node;
}

std::unique_ptr<ASTNode> Parser::expression() {
    auto node = arith_expr();
    while (current_token_.type == TokenType::EQ || current_token_.type == TokenType::NEQ ||
           current_token_.type == TokenType::LT || current_token_.type == TokenType::GT ||
           current_token_.type == TokenType::LTE || current_token_.type == TokenType::GTE) {
        Token token = current_token_;
        eat(token.type);
        node = std::make_unique<BinOpNode>(std::move(node), token, arith_expr());
    }
    return node;
}
