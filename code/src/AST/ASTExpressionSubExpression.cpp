#include "../../include/AST/ASTExpressionSubExpression.h"

//Sub Expressions.
ASTExpressionSubExpression::ASTExpressionSubExpression(ASTExpressionNode *expression) {
    this->expression = expression;
}

void ASTExpressionSubExpression::accept(Visitor *v) {
    v->visit(this);
}
