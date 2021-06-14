#include "../../include/AST/ASTExpressionUnary.h"

//Unary Expression.
ASTExpressionUnary::ASTExpressionUnary(std::string value, ASTExpressionNode* expression) {
    this->value = value;
    this->expression = expression;
}

void ASTExpressionUnary::accept(Visitor *v) {
    v->visit(this);
}