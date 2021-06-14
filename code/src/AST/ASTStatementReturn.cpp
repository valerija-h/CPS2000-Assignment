#include "../../include/AST/ASTStatementReturn.h"

//Return statement.
ASTStatementReturn::ASTStatementReturn(ASTExpressionNode *expression) {
    this->expression = expression;
}
void ASTStatementReturn::accept(Visitor *v) {
    v->visit(this);
}
