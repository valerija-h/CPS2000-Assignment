#include "../../include/AST/ASTExpressionIdentifier.h"


//Identifier.
ASTExpressionIdentifier::ASTExpressionIdentifier(std::string identifier) {
    this->identifier = identifier;
}
void ASTExpressionIdentifier::accept(Visitor *v) {
    v->visit(this);
}

