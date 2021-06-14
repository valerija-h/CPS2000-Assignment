#ifndef COMPILERSASSIGNMENT_ASTPROGRAMNODE_H
#define COMPILERSASSIGNMENT_ASTPROGRAMNODE_H

#include "ASTNode.h"

class ASTProgramNode : public ASTNode {
public:
    std::vector<ASTStatementNode*> statements;
    ASTProgramNode(std::vector<ASTStatementNode*> statements);
    virtual void accept(Visitor* v) override;
};


#endif //COMPILERSASSIGNMENT_ASTPROGRAMNODE_H
