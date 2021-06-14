#include "../../include/AST/ASTStatementBlock.h"

//Block statement.
ASTStatementBlock::ASTStatementBlock(std::vector<ASTStatementNode*> statements) {
    this->statements = statements;
}
void ASTStatementBlock::accept(Visitor *v) { v->visit(this);  }