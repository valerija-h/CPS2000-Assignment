#ifndef COMPILERSASSIGNMENT_ASTEXPRESSIONUNARY_H
#define COMPILERSASSIGNMENT_ASTEXPRESSIONUNARY_H

//Unary Expressions.
class ASTExpressionUnary : public ASTExpressionNode{
public:
    std::string value;
    ASTExpressionNode* expression;
    ASTExpressionUnary(std::string value, ASTExpressionNode* expression);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTEXPRESSIONUNARY_H
