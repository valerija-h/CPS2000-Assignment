#ifndef COMPILERSASSIGNMENT_ASTSTATEMENTRETURN_H
#define COMPILERSASSIGNMENT_ASTSTATEMENTRETURN_H

//Return Statement.
class ASTStatementReturn : public ASTStatementNode{
public:
    ASTExpressionNode* expression;
    ASTStatementReturn(ASTExpressionNode* expression);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTSTATEMENTRETURN_H
