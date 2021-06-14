#ifndef COMPILERSASSIGNMENT_ASTSTATEMENTBLOCK_H
#define COMPILERSASSIGNMENT_ASTSTATEMENTBLOCK_H

//Block Statement.
class ASTStatementBlock : public ASTStatementNode{
public:
    std::vector<ASTStatementNode*> statements;
    ASTStatementBlock(std::vector<ASTStatementNode*> statements);
    virtual void accept(Visitor* v) override;
};

#endif //COMPILERSASSIGNMENT_ASTSTATEMENTBLOCK_H
