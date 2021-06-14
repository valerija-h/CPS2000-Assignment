#include "../../include/AST/ASTFormalParams.h"

//Formal Params.
ASTFormalParams::ASTFormalParams(std::string identifier, std::string type) {
    this->identifier = identifier;
    this->type = type;
}
void ASTFormalParams::accept(Visitor *v) {
    v->visit(this);
}
