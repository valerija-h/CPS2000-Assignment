#ifndef COMPILERSASSIGNMENT_ASTEXPRESSIONLITERALFLOAT_H
#define COMPILERSASSIGNMENT_ASTEXPRESSIONLITERALFLOAT_H

class ASTExpressionLiteralFloat : public ASTExpressionLiteral {
public:
    float value;
    ASTExpressionLiteralFloat(float value);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTEXPRESSIONLITERALFLOAT_H
