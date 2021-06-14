#ifndef COMPILERSASSIGNMENT_ASTEXPRESSIONLITERAL_H
#define COMPILERSASSIGNMENT_ASTEXPRESSIONLITERAL_H

//Literal Expressions.
class ASTExpressionLiteral : public ASTExpressionNode {
public:
    ASTExpressionLiteral();
    virtual void accept(Visitor* v) = 0;
};

#endif //COMPILERSASSIGNMENT_ASTEXPRESSIONLITERAL_H
