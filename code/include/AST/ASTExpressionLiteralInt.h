#ifndef COMPILERSASSIGNMENT_ASTEXPRESSIONLITERALINT_H
#define COMPILERSASSIGNMENT_ASTEXPRESSIONLITERALINT_H

class ASTExpressionLiteralInt: public ASTExpressionLiteral{
public:
    int value;
    ASTExpressionLiteralInt(int value);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTEXPRESSIONLITERALINT_H
