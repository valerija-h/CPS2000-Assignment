#ifndef COMPILERSASSIGNMENT_ASTEXPRESSIONFUNCTIONCALL_H
#define COMPILERSASSIGNMENT_ASTEXPRESSIONFUNCTIONCALL_H

//Function Call Expressions.
class ASTExpressionFunctionCall : public ASTExpressionNode {
public:
    std::string identifier;
    std::vector<ASTExpressionNode*> actualParams; //A list of expressions.
    ASTExpressionFunctionCall(std::string identifier, std::vector<ASTExpressionNode*> actualParams);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTEXPRESSIONFUNCTIONCALL_H
