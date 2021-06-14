#ifndef COMPILERSASSIGNMENT_ASTSTATEMENTASSIGNMENT_H
#define COMPILERSASSIGNMENT_ASTSTATEMENTASSIGNMENT_H

//Assignment Statement.
class ASTStatementAssignment : public ASTStatementNode {
public:
    std::string identifier;
    ASTExpressionNode* expression;
    ASTStatementAssignment(std::string identifier, ASTExpressionNode* expression);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTSTATEMENTASSIGNMENT_H
