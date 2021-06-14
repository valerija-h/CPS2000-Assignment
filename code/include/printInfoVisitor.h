#ifndef COMPILERSASSIGNMENT_PRINTINFOVISITOR_H
#define COMPILERSASSIGNMENT_PRINTINFOVISITOR_H

#include "visitor.h"
#include <string>
#include <iostream>
#include <fstream>

class PrintInfoVisitor : public Visitor {
    int indent = 0; //Indentation for the XML file.
    std::ofstream file;
public:
    PrintInfoVisitor();
    void print_to_xml(ASTProgramNode* programNode);
    std::string get_tabs(); //Get an indented string.

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

#endif //COMPILERSASSIGNMENT_PRINTINFOVISITOR_H
