#include "../../include/AST/ASTExpressionLiteralInt.h"

//Int literal.
ASTExpressionLiteralInt::ASTExpressionLiteralInt(int value) {
    this->value = value;
}
void ASTExpressionLiteralInt::accept(Visitor *v) {
    v->visit(this);
}