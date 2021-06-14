#include "../../include/AST/ASTStatementFunctionDeclare.h"


//Function declaration.
ASTStatementFunctionDeclare::ASTStatementFunctionDeclare(std::string identifier,
                                                         std::vector<ASTFormalParams*> formalParams,
                                                         std::string type, ASTStatementNode *block) {
    this->identifier = identifier;
    this->formalParams = formalParams;
    this->type = type;
    this->block = block;
}
void ASTStatementFunctionDeclare::accept(Visitor *v) {
    v->visit(this);
}