#include "../../include/AST/ASTStatementAssignment.h"

//Assignment Statement.
ASTStatementAssignment::ASTStatementAssignment(std::string identifier, ASTExpressionNode *expression) {
    this->identifier = identifier;
    this->expression = expression;
}
void ASTStatementAssignment::accept(Visitor *v) {
    v->visit(this);
}