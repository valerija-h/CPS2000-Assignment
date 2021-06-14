#ifndef COMPILERSASSIGNMENT_ASTSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTSTATEMENTNODE_H


class ASTStatementNode : public ASTNode{
public:
    ASTStatementNode();
    virtual void accept(Visitor* v) = 0;
};

#endif //COMPILERSASSIGNMENT_ASTSTATEMENTNODE_H
