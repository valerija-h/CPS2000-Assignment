#ifndef COMPILERSASSIGNMENT_ASTEXPRESSIONSUBEXPRESSION_H
#define COMPILERSASSIGNMENT_ASTEXPRESSIONSUBEXPRESSION_H

//Subexpressions.
class ASTExpressionSubExpression: public ASTExpressionNode{
public:
    ASTExpressionNode* expression;
    ASTExpressionSubExpression(ASTExpressionNode* expression);
    virtual void accept(Visitor* v) override;
};


#endif //COMPILERSASSIGNMENT_ASTEXPRESSIONSUBEXPRESSION_H
