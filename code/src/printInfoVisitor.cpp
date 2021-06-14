#include "../include/printInfoVisitor.h"

PrintInfoVisitor::PrintInfoVisitor() {}

void PrintInfoVisitor::print_to_xml(ASTProgramNode* programNode){
    //Create a file for XML output.
    file.open("../XMLOutput.xml");
    if(file.is_open()){
        programNode->accept(this);
    } else {
        std::cout << "Unable to open file to write.";
    }
    file.close();
}

void PrintInfoVisitor::visit(ASTStatementAssignment *node) {
    file << get_tabs() << "<Assignment>" <<std::endl;
    indent++;
    file << get_tabs() << "<Identifier>" << node->identifier << "</Identifier>" << std::endl;
    file << get_tabs() << "<Expression>" <<std::endl;
    indent++;
    node->expression->accept(this);
    indent--;
    file << get_tabs() << "</Expression>" <<std::endl;
    indent--;
    file << get_tabs() << "</Assignment>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTStatementPrint *node) {
    file << get_tabs() << "<PrintStatement>" <<std::endl;
    indent++;
    file << get_tabs() << "<Expression>" <<std::endl;
    indent++;
    node->expression->accept(this);
    indent--;
    file << get_tabs() << "</Expression>" <<std::endl;
    indent--;
    file << get_tabs() << "</PrintStatement>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTStatementBlock *node) {
    file << get_tabs() << "<BlockStatement>" <<std::endl;
    indent++;
    for(auto &statement : node->statements){
        statement->accept(this);
    }
    indent--;
    file << get_tabs() << "</BlockStatement>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTStatementIf *node) {
    file << get_tabs() << "<IfStatement>" <<std::endl;
    indent++;
    file << get_tabs() << "<Expression>" <<std::endl;
    indent++;
    node->expression->accept(this);
    indent--;
    file << get_tabs() << "</Expression>" <<std::endl;
    node->ifBlock->accept(this); //Get block.
    indent--;
    file << get_tabs() << "</IfStatement>" <<std::endl;
    //If there is an else.
    if(node->elseBlock != nullptr){
        file << get_tabs() << "<ElseStatement>" <<std::endl;
        indent++;
        node->elseBlock->accept(this);
        indent--;
        file << get_tabs() << "</ElseStatement>" <<std::endl;
    }
}

void PrintInfoVisitor::visit(ASTStatementFor *node) {
    file << get_tabs() << "<ForStatement>" <<std::endl;
    indent++;
    if(node->varDeclare)
        node->varDeclare->accept(this); //Variable Declaration.
    file << get_tabs() << "<Expression>" <<std::endl;
    indent++;
    node->expression->accept(this);
    indent--;
    file << get_tabs() << "</Expression>" <<std::endl;
    if(node->assignment)
        node->assignment->accept(this); //Assignment.
    indent--;
    file << get_tabs() << "</ForStatement>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTStatementReturn *node) {
    file << get_tabs() << "<ReturnStatement>" <<std::endl;
    indent++;
    file << get_tabs() << "<Expression>" <<std::endl;
    indent++;
    node->expression->accept(this);
    indent--;
    file << get_tabs() << "</Expression>" <<std::endl;
    indent--;
    file << get_tabs() << "</ReturnStatement>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTFormalParams *node) {
    file << get_tabs() << "<FormalParameter Type=\"" << node->type << "\">" <<std::endl;
    indent++;
    file << get_tabs() << "<Identifier>" << node->identifier << "</Identifier>" << std::endl;
    indent--;
    file << get_tabs() << "</FormalParameter>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTStatementFunctionDeclare* node) {
    file << get_tabs() << "<FunctionDeclaration Type=\"" << node->type << "\">" <<std::endl;
    indent++;
    file << get_tabs() << "<Identifier>" << node->identifier << "</Identifier>" << std::endl; //Identifer.
    file << get_tabs() << "<FormalParameters>" <<std::endl; //Formal Params.
    indent++;
    for(auto &formalParam : node->formalParams){
        formalParam->accept(this);
    }
    indent--;
    file << get_tabs() << "</FormalParameters>" <<std::endl;
    node->block->accept(this); //Block.
    indent--;
    file << get_tabs() << "</FunctionDeclaration>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTExpressionSubExpression *node) {
    node->expression->accept(this);
}

void PrintInfoVisitor::visit(ASTExpressionUnary *node) {
    file << get_tabs() << "<UnaryExpression Op=\"" << node->value << "\">" <<std::endl;
    indent++;
    node->expression->accept(this);
    indent--;
    file << get_tabs() << "</UnaryExpression>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTExpressionLiteralBool *node) {
    if(node->value)
        file << get_tabs() << "<BoolLiteral>true</BoolLiteral>" <<std::endl;
    else
        file << get_tabs() << "<BoolLiteral>false</BoolLiteral>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTExpressionLiteralFloat *node) {
    file << get_tabs() << "<FloatLiteral>" << node->value << "</FloatLiteral>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTExpressionLiteralInt *node) {
    file << get_tabs() << "<IntLiteral>" << node->value << "</IntLiteral>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTExpressionIdentifier *node) {
    file << get_tabs() << "<Identifier>" << node->identifier << "</Identifier>" << std::endl; //Identifer.
}

void PrintInfoVisitor::visit(ASTExpressionFunctionCall *node) {
    file << get_tabs() << "<FunctionCall>" <<std::endl;
    indent++;
    file << get_tabs() << "<Identifier>" << node->identifier << "</Identifier>" << std::endl;
    for(auto &actualParam : node->actualParams){
        actualParam->accept(this);
    }
    indent--;
    file << get_tabs() << "</FunctionCall>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTExpressionBinary *node) {
    file << get_tabs() << "<BinaryExpression Op=\"" << node->op << "\">" <<std::endl;
    indent++;
    node->LHS->accept(this);
    node->RHS->accept(this);
    indent--;
    file << get_tabs() << "</BinaryExpression>" <<std::endl;
}

std::string PrintInfoVisitor::get_tabs() {
    std::string tabs = "";
    for (int t = 0; t<indent; t++) tabs.append("\t");
    return tabs;
}

void PrintInfoVisitor::visit(ASTProgramNode *node) {
    file << get_tabs() << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" <<std::endl;
    file << get_tabs() << "<ProgramNode>" <<std::endl;
    indent++;
    //For each statement - call accept.
    for(auto &statement : node->statements){
        statement->accept(this);
    }
    indent--;
    file << get_tabs() << "</ProgramNode>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTStatementVarDeclare *node) {
    file << get_tabs() << "<VariableDeclaration>" <<std::endl;
    indent++;
    file << get_tabs() << "<Variable Type=\"" << node->type << "\">" << node->identifier << "</Variable>" <<std::endl;
    file << get_tabs() << "<Expression>" <<std::endl;
    indent++;
    node->expression->accept(this);
    indent--;
    file << get_tabs() << "</Expression>" <<std::endl;
    indent--;
    file << get_tabs() << "</VariableDeclaration>" <<std::endl;
}

void PrintInfoVisitor::visit(ASTStatementNode *node) {}
void PrintInfoVisitor::visit(ASTExpressionNode *node) {}
