#ifndef COMPILERSASSIGNMENT_ASTEXPRESSIONBINARY_H
#define COMPILERSASSIGNMENT_ASTEXPRESSIONBINARY_H

//Binary Expressions.
class ASTExpressionBinary: public ASTExpressionNode{
public:
    ASTExpressionNode* LHS;
    ASTExpressionNode* RHS;
    std::string op;
    ASTExpressionBinary(ASTExpressionNode* LHS,ASTExpressionNode* RHS,std::string op);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTEXPRESSIONBINARY_H
