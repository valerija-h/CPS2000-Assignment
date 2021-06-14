#ifndef COMPILERSASSIGNMENT_ASTSTATEMENTVARDECLARE_H
#define COMPILERSASSIGNMENT_ASTSTATEMENTVARDECLARE_H

//Variable Declaration Statement.
class ASTStatementVarDeclare : public ASTStatementNode{
public:
    std::string identifier;
    std::string type;
    ASTExpressionNode* expression;
    ASTStatementVarDeclare(std::string identifier, std::string type, ASTExpressionNode* expression);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTSTATEMENTVARDECLARE_H
