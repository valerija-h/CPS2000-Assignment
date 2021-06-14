#ifndef COMPILERSASSIGNMENT_PARSER_H
#define COMPILERSASSIGNMENT_PARSER_H

#include <math.h>
#include <sstream>
#include <vector>

class Parser {
public:
    /** VARIABLES **/
    Lexer* lexer; //Lexer that sends tokens.
    Lexer::Token currToken = Lexer::Token(Lexer::TOK_EOF);  //The current token.

    /** FUNCTIONS **/
    Parser(Lexer* lexer);
    ASTProgramNode* parse();
    ASTStatementNode* get_statement(); //Returns a statement.
    ASTFormalParams* get_formal_params(); //Returns a formal params object.

    //Expressions.
    ASTExpressionNode* get_expression();
    ASTExpressionNode* parse_simple_expression();
    ASTExpressionNode* parse_term();
    ASTExpressionNode* parse_factor();

    //Statements.
    ASTStatementNode* parse_var_declare();
    ASTStatementNode* parse_assignment();
    ASTStatementNode* parse_print_statement();
    ASTStatementNode* parse_block();
    ASTStatementNode* parse_if_statement();
    ASTStatementNode* parse_for_statement();
    ASTStatementNode* parse_function_declare();

    //For printing syntax errors.
    void print_error(std::string string);
};

#endif //COMPILERSASSIGNMENT_PARSER_H
