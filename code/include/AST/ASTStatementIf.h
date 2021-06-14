#ifndef COMPILERSASSIGNMENT_ASTSTATEMENTIF_H
#define COMPILERSASSIGNMENT_ASTSTATEMENTIF_H

//If Statement.
class ASTStatementIf : public ASTStatementNode{
public:
    ASTExpressionNode* expression;
    ASTStatementNode* ifBlock;
    ASTStatementNode* elseBlock = nullptr;
    ASTStatementIf( ASTExpressionNode* expression,ASTStatementNode* ifBlock);
    ASTStatementIf( ASTExpressionNode* expression,ASTStatementNode* ifBlock, ASTStatementNode* elseBlock);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTSTATEMENTIF_H
