#include "ast.h"
#include <stdexcept>
#include <unordered_map>

// グローバルなシンボルテーブルを外部から参照
extern std::unordered_map<std::string, double> symbol_table;

// --- コンストラクタの実装 ---
NumberNode::NumberNode(Token token) : token(std::move(token)) {}
VarNode::VarNode(Token token) : token(std::move(token)) {}
BinOpNode::BinOpNode(std::unique_ptr<ASTNode> l, Token o, std::unique_ptr<ASTNode> r)
    : left(std::move(l)), op(std::move(o)), right(std::move(r)) {}
VarDeclNode::VarDeclNode(std::string name, std::unique_ptr<ASTNode> e)
    : var_name(std::move(name)), expr(std::move(e)) {}
IfNode::IfNode(std::unique_ptr<ASTNode> cond, std::unique_ptr<ASTNode> then_b, std::unique_ptr<ASTNode> else_b)
    : condition(std::move(cond)), then_branch(std::move(then_b)), else_branch(std::move(else_b)) {}


// --- evaluateメソッドの実装 ---
double NumberNode::evaluate() const { return token.value; }

double VarNode::evaluate() const {
    if (symbol_table.count(token.name)) return symbol_table.at(token.name);
    throw std::runtime_error("Runtime error: '" + token.name + "' is not defined.");
}

double BinOpNode::evaluate() const {
    double left_val = left->evaluate();
    double right_val = right->evaluate();
    switch(op.type) {
        case TokenType::PLUS: return left_val + right_val;
        case TokenType::MINUS: return left_val - right_val;
        case TokenType::MUL: return left_val * right_val;
        case TokenType::DIV:
             if (right_val == 0) throw std::runtime_error("Runtime error: Division by zero.");
             return left_val / right_val;
        case TokenType::EQ: return left_val == right_val;
        case TokenType::NEQ: return left_val != right_val;
        case TokenType::LT: return left_val < right_val;
        case TokenType::GT: return left_val > right_val;
        case TokenType::LTE: return left_val <= right_val;
        case TokenType::GTE: return left_val >= right_val;
        default: throw std::runtime_error("Runtime error: invalid binary operator");
    }
}

double VarDeclNode::evaluate() const {
    double val = expr->evaluate();
    symbol_table[var_name] = val;
    return val;
}

double CompoundNode::evaluate() const {
    double result = 0.0;
    for (const auto& child : children) {
        result = child->evaluate();
    }
    return result;
}

double IfNode::evaluate() const {
    if (condition->evaluate() != 0) {
        return then_branch->evaluate();
    } else if (else_branch) {
        return else_branch->evaluate();
    }
    return 0.0;
}
