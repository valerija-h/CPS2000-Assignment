#ifndef COMPILERSASSIGNMENT_ASTNODE_H
#define COMPILERSASSIGNMENT_ASTNODE_H

#include "../visitor.h"

class ASTNode {
public:
    ASTNode();
    virtual void accept(Visitor* v) = 0;
};

#endif //COMPILERSASSIGNMENT_ASTNODE_H
