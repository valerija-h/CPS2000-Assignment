#include "../../include/AST/ASTProgramNode.h"

ASTProgramNode::ASTProgramNode(std::vector<ASTStatementNode *> statements) {
    this->statements = statements;
}

void ASTProgramNode::accept(Visitor *v) {
    v->visit(this);
}