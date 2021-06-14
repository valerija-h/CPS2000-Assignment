#ifndef COMPILERSASSIGNMENT_VISITOR_H
#define COMPILERSASSIGNMENT_VISITOR_H

class ASTNode;
class ASTProgramNode;
class ASTStatementNode;
class ASTStatementVarDeclare;
class ASTStatementAssignment;
class ASTStatementPrint;
class ASTStatementBlock;
class ASTStatementIf;
class ASTStatementFor;
class ASTStatementReturn;
class ASTFormalParams;
class ASTStatementFunctionDeclare;
class ASTExpressionNode;
class ASTExpressionSubExpression;
class ASTExpressionUnary;
class ASTExpressionLiteral;
class ASTExpressionLiteralBool;
class ASTExpressionLiteralInt;
class ASTExpressionLiteralFloat;
class ASTExpressionIdentifier;
class ASTExpressionFunctionCall;
class ASTExpressionBinary;

class Visitor{
public:
    virtual void visit(ASTProgramNode*) = 0;
    virtual void visit(ASTStatementNode*) = 0;
    virtual void visit(ASTStatementVarDeclare*) = 0;
    virtual void visit(ASTStatementAssignment*) = 0;
    virtual void visit(ASTStatementPrint*) = 0;
    virtual void visit(ASTStatementBlock*) = 0;
    virtual void visit(ASTStatementIf*) = 0;
    virtual void visit(ASTStatementFor*) = 0;
    virtual void visit(ASTStatementReturn*) = 0;
    virtual void visit(ASTFormalParams*) = 0;
    virtual void visit(ASTStatementFunctionDeclare*) = 0;
    virtual void visit(ASTExpressionNode*) = 0;
    virtual void visit(ASTExpressionSubExpression*) = 0;
    virtual void visit(ASTExpressionUnary*) = 0;
    virtual void visit(ASTExpressionLiteralBool*) = 0;
    virtual void visit(ASTExpressionLiteralFloat*) = 0;
    virtual void visit(ASTExpressionLiteralInt*) = 0;
    virtual void visit(ASTExpressionIdentifier*) = 0;
    virtual void visit(ASTExpressionFunctionCall*) = 0;
    virtual void visit(ASTExpressionBinary*) = 0;
};

#endif //COMPILERSASSIGNMENT_VISITOR_H
