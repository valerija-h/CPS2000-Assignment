#include "../../include/AST/ASTStatementFor.h"

//For statement.
ASTStatementFor::ASTStatementFor(ASTStatementNode* varDeclare, ASTExpressionNode *expression,
                                 ASTStatementNode* assignment, ASTStatementNode *block) {
    this->varDeclare = varDeclare;
    this->expression = expression;
    this->assignment = assignment;
    this->block = block;
}
void ASTStatementFor::accept(Visitor *v) {
    v->visit(this);
}
