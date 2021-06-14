#include "../../include/AST/ASTExpressionLiteralBool.h"

//Bool literal.
ASTExpressionLiteralBool::ASTExpressionLiteralBool(bool value) {
    this->value = value;
}
void ASTExpressionLiteralBool::accept(Visitor *v) {
    v->visit(this);
}
