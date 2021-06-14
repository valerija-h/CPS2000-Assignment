#ifndef COMPILERSASSIGNMENT_ASTEXPRESSIONIDENTIFIER_H
#define COMPILERSASSIGNMENT_ASTEXPRESSIONIDENTIFIER_H

//Identifier Expressions.
class ASTExpressionIdentifier : public ASTExpressionNode {
public:
    std::string identifier;
    ASTExpressionIdentifier(std::string identifier);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTEXPRESSIONIDENTIFIER_H
