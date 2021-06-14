#ifndef COMPILERSASSIGNMENT_ASTSTATEMENTFOR_H
#define COMPILERSASSIGNMENT_ASTSTATEMENTFOR_H

//For Statement.
class ASTStatementFor : public ASTStatementNode{
public:
    ASTStatementNode* varDeclare;
    ASTExpressionNode* expression;
    ASTStatementNode* assignment;
    ASTStatementNode* block;
    ASTStatementFor(ASTStatementNode* varDeclare, ASTExpressionNode* expression, ASTStatementNode* assignment, ASTStatementNode* block);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTSTATEMENTFOR_H
