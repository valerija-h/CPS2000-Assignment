#include "../include/header.h"

int main() {
    //Task 1
    Lexer *lexer = new Lexer("../Test.txt");
    //Task 2
    Parser parser = Parser(lexer);
    ASTProgramNode* program = parser.parse();
    //Task 3
    PrintInfoVisitor* printInfoVisitor = new PrintInfoVisitor();
    printInfoVisitor->print_to_xml(program);
    //Task 4
    SemanticAnalysisVisitor semanticAnalysisVisitor = SemanticAnalysisVisitor();
    semanticAnalysisVisitor.visit(program);
    return 0;
}