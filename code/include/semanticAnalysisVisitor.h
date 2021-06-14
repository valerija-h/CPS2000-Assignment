#ifndef COMPILERSASSIGNMENT_SEMANTICANALYSISVISITOR_H
#define COMPILERSASSIGNMENT_SEMANTICANALYSISVISITOR_H

#include "visitor.h"
#include <stack>

class SemanticAnalysisVisitor : public Visitor {
    std::vector<SymbolTable*> symbolTables;
    std::string currentLiteralType = ""; //Keeps track of literal types for functions and for assignments.
    bool enableBinaryChecking = false; //Flag for 'if', 'for' and 'print' statements.
    std::string binaryLiteralType = "";
public:
    SemanticAnalysisVisitor();
    void addTable(); //Add a new symbol to the top of the stack.
    SymbolTable* getLastTable(); //Get the last added symbol table from the stack.
    void removeLastTable(); //Remove the last added symbol table from the stack.
    Symbol* checkInTables(std::string identifier); //Go through each table in the stack to check for an identifier.

    //Visit functions.
    virtual void visit(ASTProgramNode* node) override;
    virtual void visit(ASTStatementNode *node) override;
    virtual void visit(ASTStatementVarDeclare *node) override;
    virtual void visit(ASTStatementAssignment *node) override;
    virtual void visit(ASTStatementPrint *node) override;
    virtual void visit(ASTStatementBlock *node) override;
    virtual void visit(ASTStatementIf *node) override;
    virtual void visit(ASTStatementFor *node) override;
    virtual void visit(ASTStatementReturn *node) override;
    virtual void visit(ASTFormalParams *node) override;
    virtual void visit(ASTStatementFunctionDeclare* node) override;
    virtual void visit(ASTExpressionNode *node) override;
    virtual void visit(ASTExpressionSubExpression *node) override;
    virtual void visit(ASTExpressionUnary *node) override;
    virtual void visit(ASTExpressionLiteralBool *node) override;
    virtual void visit(ASTExpressionLiteralFloat *node) override;
    virtual void visit(ASTExpressionLiteralInt *node) override;
    virtual void visit(ASTExpressionIdentifier *node) override;
    virtual void visit(ASTExpressionFunctionCall *node) override;
    virtual void visit(ASTExpressionBinary *node) override;
};

#endif //COMPILERSASSIGNMENT_SEMANTICANALYSISVISITOR_H
