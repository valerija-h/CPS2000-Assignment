#include "../../include/AST/ASTExpressionBinary.h"

//Expression binary.
ASTExpressionBinary::ASTExpressionBinary(ASTExpressionNode *LHS, ASTExpressionNode *RHS, std::string op) {
    this->LHS = LHS;
    this->RHS = RHS;
    this->op = op;
}
void ASTExpressionBinary::accept(Visitor *v) {
    v->visit(this);
}