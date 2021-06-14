#include "../../include/AST/ASTStatementIf.h"

//If statement.
ASTStatementIf::ASTStatementIf(ASTExpressionNode* expression, ASTStatementNode* ifBlock) {
    this->expression = expression;
    this->ifBlock = ifBlock;
    this->elseBlock = nullptr;
}
ASTStatementIf::ASTStatementIf(ASTExpressionNode* expression, ASTStatementNode* ifBlock,
                               ASTStatementNode* elseBlock) {
    this->expression = expression;
    this->ifBlock = ifBlock;
    this->elseBlock = elseBlock;
}
void ASTStatementIf::accept(Visitor *v) { v->visit(this);  }
