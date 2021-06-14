#include "../../include/AST/ASTExpressionLiteralFloat.h"

//Float literal.
ASTExpressionLiteralFloat::ASTExpressionLiteralFloat(float value) {
    this->value = value;
}
void ASTExpressionLiteralFloat::accept(Visitor *v) {
    v->visit(this);
}

