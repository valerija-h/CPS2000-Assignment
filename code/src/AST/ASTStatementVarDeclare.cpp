#include "../../include/AST/ASTStatementVarDeclare.h"

//Variable Declaration.
ASTStatementVarDeclare::ASTStatementVarDeclare(std::string identifier, std::string type,
                                               ASTExpressionNode *expression) {
    this->identifier = identifier;
    this->type = type;
    this->expression = expression;
}
void ASTStatementVarDeclare::accept(Visitor *v) {
    v->visit(this);
}