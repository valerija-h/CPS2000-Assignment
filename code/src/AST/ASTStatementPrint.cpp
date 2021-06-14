#include "../../include/AST/ASTStatementPrint.h"

//Print statement.
ASTStatementPrint::ASTStatementPrint(ASTExpressionNode *expression) {
    this->expression = expression;
}
void ASTStatementPrint::accept(Visitor *v) {
    v->visit(this);
}


