#ifndef COMPILERSASSIGNMENT_ASTEXPRESSIONLITERALBOOL_H
#define COMPILERSASSIGNMENT_ASTEXPRESSIONLITERALBOOL_H

class ASTExpressionLiteralBool : public ASTExpressionLiteral{
public:
    bool value;
    ASTExpressionLiteralBool(bool value);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTEXPRESSIONLITERALBOOL_H
