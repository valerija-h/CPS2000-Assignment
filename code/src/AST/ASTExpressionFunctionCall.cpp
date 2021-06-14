#include "../../include/AST/ASTExpressionFunctionCall.h"


//Function call.
ASTExpressionFunctionCall::ASTExpressionFunctionCall(std::string identifier, std::vector<ASTExpressionNode*> actualParams){
    this->identifier = identifier;
    this->actualParams = actualParams;
}
void ASTExpressionFunctionCall::accept(Visitor *v) {
    v->visit(this);
}
