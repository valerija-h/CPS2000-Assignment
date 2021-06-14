#ifndef COMPILERSASSIGNMENT_ASTEXPRESSIONNODE_H
#define COMPILERSASSIGNMENT_ASTEXPRESSIONNODE_H

#include "ASTNode.h"
#include <vector>

class ASTExpressionNode : public ASTNode{
public:
    ASTExpressionNode();
    virtual void accept(Visitor* v) = 0;
};


#endif //COMPILERSASSIGNMENT_ASTEXPRESSIONNODE_H
