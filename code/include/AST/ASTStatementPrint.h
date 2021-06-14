#ifndef COMPILERSASSIGNMENT_ASTSTATEMENTPRINT_H
#define COMPILERSASSIGNMENT_ASTSTATEMENTPRINT_H

//Print Statement.
class ASTStatementPrint : public ASTStatementNode {
public:
    ASTExpressionNode* expression;
    ASTStatementPrint(ASTExpressionNode* expression);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTSTATEMENTPRINT_H
