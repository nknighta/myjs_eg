#ifndef AST_H
#define AST_H

#include "token.h"
#include <memory>
#include <vector>
#include <string>

// ASTの基底ノードクラス
struct ASTNode {
    virtual ~ASTNode() = default;
    virtual double evaluate() const = 0;
};

// 各ノードの宣言
struct NumberNode;
struct VarNode;
struct BinOpNode;
struct VarDeclNode;
struct CompoundNode;
struct IfNode;

// 数値ノード
struct NumberNode : public ASTNode {
    Token token;
    NumberNode(Token token);
    double evaluate() const override;
};

// 変数参照ノード
struct VarNode : public ASTNode {
    Token token;
    VarNode(Token token);
    double evaluate() const override;
};

// 二項演算ノード
struct BinOpNode : public ASTNode {
    std::unique_ptr<ASTNode> left;
    Token op;
    std::unique_ptr<ASTNode> right;
    BinOpNode(std::unique_ptr<ASTNode> l, Token o, std::unique_ptr<ASTNode> r);
    double evaluate() const override;
};

// 変数宣言ノード
struct VarDeclNode : public ASTNode {
    std::string var_name;
    std::unique_ptr<ASTNode> expr;
    VarDeclNode(std::string name, std::unique_ptr<ASTNode> e);
    double evaluate() const override;
};

// 複数の文をまとめるノード
struct CompoundNode : public ASTNode {
    std::vector<std::unique_ptr<ASTNode>> children;
    double evaluate() const override;
};

// If-Else ノード
struct IfNode : public ASTNode {
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> then_branch;
    std::unique_ptr<ASTNode> else_branch;
    IfNode(std::unique_ptr<ASTNode> cond, std::unique_ptr<ASTNode> then_b, std::unique_ptr<ASTNode> else_b);
    double evaluate() const override;
};

#endif // AST_H
