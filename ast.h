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
struct AssignmentNode; // <-- AssignmentNode の前方宣言を追加
struct CompoundNode;
struct IfNode;
struct WhileNode;

// (他のノード宣言は変更なし)
struct NumberNode : public ASTNode {
    Token token;
    NumberNode(Token token);
    double evaluate() const override;
};
struct VarNode : public ASTNode {
    Token token;
    VarNode(Token token);
    double evaluate() const override;
};
struct BinOpNode : public ASTNode {
    std::unique_ptr<ASTNode> left;
    Token op;
    std::unique_ptr<ASTNode> right;
    BinOpNode(std::unique_ptr<ASTNode> l, Token o, std::unique_ptr<ASTNode> r);
    double evaluate() const override;
};
struct VarDeclNode : public ASTNode {
    std::string var_name;
    std::unique_ptr<ASTNode> expr;
    VarDeclNode(std::string name, std::unique_ptr<ASTNode> e);
    double evaluate() const override;
};

// NEW: 代入ノード
struct AssignmentNode : public ASTNode {
    Token var_token;
    std::unique_ptr<ASTNode> expr;
    AssignmentNode(Token token, std::unique_ptr<ASTNode> e);
    double evaluate() const override;
};

struct CompoundNode : public ASTNode {
    std::vector<std::unique_ptr<ASTNode>> children;
    double evaluate() const override;
};
struct IfNode : public ASTNode {
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> then_branch;
    std::unique_ptr<ASTNode> else_branch;
    IfNode(std::unique_ptr<ASTNode> cond, std::unique_ptr<ASTNode> then_b, std::unique_ptr<ASTNode> else_b);
    double evaluate() const override;
};
struct WhileNode : public ASTNode {
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> body;
    WhileNode(std::unique_ptr<ASTNode> cond, std::unique_ptr<ASTNode> body);
    double evaluate() const override;
};

#endif // AST_H
