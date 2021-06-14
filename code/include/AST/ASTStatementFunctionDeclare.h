#ifndef COMPILERSASSIGNMENT_ASTSTATEMENTFUNCTIONDECLARE_H
#define COMPILERSASSIGNMENT_ASTSTATEMENTFUNCTIONDECLARE_H

//Function Declaration Statement.
class ASTStatementFunctionDeclare : public ASTStatementNode{
public:
    std::string identifier;
    std::vector<ASTFormalParams*> formalParams;
    std::string type;
    ASTStatementNode* block;
    ASTStatementFunctionDeclare(std::string identifier,std::vector<ASTFormalParams*> formalParams,std::string type,ASTStatementNode* block);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTSTATEMENTFUNCTIONDECLARE_H
