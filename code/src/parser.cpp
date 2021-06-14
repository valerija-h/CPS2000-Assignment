#include "../include/parser.h"

Parser::Parser(Lexer* lexer){
    this->lexer = lexer;
}

ASTProgramNode* Parser::parse(){
    //Create a vector of statement nodes.
    std::vector<ASTStatementNode*> statements;
    currToken = lexer->get_next_token();
    //Read each token from the lexer until an EOF token is reached.
    while(currToken.getTokenType() != Lexer::TOK_EOF){
        ASTStatementNode* currentStatement = get_statement();
        currToken = lexer->get_next_token();
        //Add each statement to the vector of statements.
        statements.push_back(currentStatement);
    }
    //Return a program node with vector of statements.
    return new ASTProgramNode(statements);
}

ASTStatementNode* Parser::get_statement() {
    switch(currToken.getTokenType())
    {
        case Lexer::TOK_VAR_DECLARE: {
            ASTStatementNode *varDeclare = parse_var_declare();
            //If the next token type is not a semicolon ';', throw an error.
            currToken = lexer->get_next_token();
            if (currToken.getTokenType() != Lexer::TOK_SEMICOLON) {
                print_error("Expected ';' after equals in variable declaration.");
                exit(EXIT_FAILURE);
            }
            return varDeclare;
        }
        case Lexer::TOK_ID: {
            ASTStatementNode *assignmentNode = parse_assignment();
            //If the next token type is not a semicolon ';', throw an error.
            currToken = lexer->get_next_token();
            if (currToken.getTokenType() != Lexer::TOK_SEMICOLON) {
                print_error("Expected ';' after expression in assignment statement.");
                exit(EXIT_FAILURE);
            }
            return assignmentNode;
        }
        case Lexer::TOK_PRINT:{
            ASTStatementNode* printNode = parse_print_statement();
            //If the next token type is not a semicolon ';', throw an error.
            currToken = lexer->get_next_token();
            if(currToken.getTokenType() != Lexer::TOK_SEMICOLON){
                print_error("Expected ';' after expression in print statement.");
                exit(EXIT_FAILURE);
            }
            return printNode;
        }
        case Lexer::TOK_IF:
            return parse_if_statement();
        case Lexer::TOK_LEFT_CURLY:
            return parse_block();
        case Lexer::TOK_FOR:
            return parse_for_statement();
        case Lexer::TOK_RETURN:{
            //Get expression.
            ASTExpressionNode* expressionNode = get_expression();
            //If the next token type is not a semicolon ';', throw an error.
            if(lexer->check_next_token() != Lexer::TOK_SEMICOLON){
                print_error("Expected semicolon after expression in a return statement.");
                exit(EXIT_FAILURE);
            }
            currToken = lexer->get_next_token();
            return new ASTStatementReturn(expressionNode);
        }
        case Lexer::TOK_FUN_DECLARE:
            return parse_function_declare();
        default:
            print_error("Unrecognizable statement token.");
            exit(EXIT_FAILURE);
    }
}

ASTStatementNode* Parser::parse_function_declare() {
    //Check for identifier.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_ID){
        print_error("Expected identifier after 'fn' in a function declaration.");
        exit(EXIT_FAILURE);
    }
    std::string identifier = currToken.getTokenName();
    //Check for left parenthesis.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_LEFT_PAR){
        print_error("Expected '(' after identifier in a function declaration.");
        exit(EXIT_FAILURE);
    }
    //Until the next token is ')', get a list of formal params.
    std::vector<ASTFormalParams*> formalParams;
    while(currToken.getTokenType() != Lexer::TOK_RIGHT_PAR){
        formalParams.push_back(get_formal_params());
        currToken = lexer->get_next_token();
        //If the next token isn't a comma or ')', throw an error.
        if(currToken.getTokenType() != Lexer::TOK_RIGHT_PAR && currToken.getTokenType() != Lexer::TOK_COMMA){
            print_error("Expected ',' or ')' for the list of formal params in function declaration.");
            exit(EXIT_FAILURE);
        }
    }
    //Check for colon.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_COLON){
        print_error("Expected colon after formal params in a function declaration.");
        exit(EXIT_FAILURE);
    }
    //Check for type.
    currToken = lexer->get_next_token();
    Lexer::TokenType currTokenType = currToken.getTokenType();
    if((currTokenType != Lexer::TOK_INT_TYPE) && (currTokenType != Lexer::TOK_FLOAT_TYPE) && (currTokenType != Lexer::TOK_BOOL_TYPE)) {
        print_error("Expected valid type in formal params.");
        exit(EXIT_FAILURE);
    }
    std::string tokenType = currToken.token_to_string();
    ASTStatementNode* blockStatement = parse_block(); //Get block statement.
    return new ASTStatementFunctionDeclare(identifier, formalParams, tokenType, blockStatement);
}

ASTFormalParams* Parser::get_formal_params() {
    //Check for identifier.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_ID){
        print_error("Expected identifier in formal params.");
        exit(EXIT_FAILURE);
    }
    std::string identifier = currToken.getTokenName();
    //Check for colon.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_COLON){
        print_error("Expected colon in formal params.");
        exit(EXIT_FAILURE);
    }
    //Check for type.
    currToken = lexer->get_next_token();
    Lexer::TokenType currTokenType = currToken.getTokenType();
    if((currTokenType != Lexer::TOK_INT_TYPE) && (currTokenType != Lexer::TOK_FLOAT_TYPE) && (currTokenType != Lexer::TOK_BOOL_TYPE)) {
        print_error("Expected type in formal params.");
        exit(EXIT_FAILURE);
    }
    return new ASTFormalParams(identifier,currToken.token_to_string());
}

ASTStatementNode* Parser::parse_for_statement() {
    //Check for left parenthesis.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_LEFT_PAR){
        print_error("Expected '(' after 'if' in a for statement");
        exit(EXIT_FAILURE);
    }
    //Get for variable declaration option.
    ASTStatementNode* varDeclare = nullptr;
    if(lexer->check_next_token() == Lexer::TOK_VAR_DECLARE){
        currToken = lexer->get_next_token();
        varDeclare = parse_var_declare();
    }
    //Check for a semicolon.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_SEMICOLON) {
        print_error("Expected ';' after variable declaration in a for statement.");
        exit(EXIT_FAILURE);
    }
    //Get the expression.
    ASTExpressionNode* expressionNode = get_expression();
    //Check for a semicolon.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_SEMICOLON) {
        print_error("Expected ';' after expression in a for statement.");
        exit(EXIT_FAILURE);
    }
    //Check for an assignment option.
    ASTStatementNode* assignment = nullptr;
    if(lexer->check_next_token() == Lexer::TOK_ID){
        currToken = lexer->get_next_token();
        assignment = parse_assignment();
    }
    //Check for a right parenthesis.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_RIGHT_PAR) {
        print_error("Expected ')' after assignment in a for statement.");
        exit(EXIT_FAILURE);
    }
    //Get a block statement.
    ASTStatementNode* blockStatement = parse_block();
    return new ASTStatementFor(varDeclare, expressionNode, assignment, blockStatement);
}

ASTStatementNode* Parser::parse_if_statement() {
    //Check for left parenthesis.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_LEFT_PAR){
        print_error("Expected '(' after 'if' in an if statement.");
        exit(EXIT_FAILURE);
    }
    //Get expression.
    ASTExpressionNode* expressionNode = get_expression();
    //Check for right parenthesis.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_RIGHT_PAR){
        print_error("Expected ')' after expression in an if statement.");
        exit(EXIT_FAILURE);
    }
    //Get block statement.
    ASTStatementNode* ifBlock = parse_block();
    //If 'else' statement is found.
    if(lexer->check_next_token() == Lexer::TOK_ELSE){
        currToken = lexer->get_next_token(); //Skip else.
        ASTStatementNode* elseBlock = parse_block(); //Get the 'else' block.
        return new ASTStatementIf(expressionNode,ifBlock,elseBlock);
    }
    return new ASTStatementIf(expressionNode, ifBlock);
}

ASTStatementNode* Parser::parse_block() {
    //Check for left curly bracket.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_LEFT_CURLY){
        print_error("Expected '{' for block statement.");
        exit(EXIT_FAILURE);
    }
    currToken = lexer->get_next_token();
    //Make a new list of vector statements.
    std::vector<ASTStatementNode*> statements;
    //Keep adding statements till right curly bracket '}' is encountered.
    while(currToken.getTokenType() != Lexer::TOK_RIGHT_CURLY){
        statements.push_back(get_statement());
        currToken = lexer->get_next_token();
    }
    return new ASTStatementBlock(statements);
}

ASTStatementNode* Parser::parse_var_declare() {
    //If the next token type is not and identifier throw an error.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_ID){
        print_error("Expected identifier after 'var' in variable declaration.");
        exit(EXIT_FAILURE);
    }
    std::string identifier = currToken.getTokenName();
    //If the next token type is not a colon ':', throw an error.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_COLON){
        print_error("Expected colon after identifier in variable declaration.");
        exit(EXIT_FAILURE);
    }
    //Check for variable type.
    currToken = lexer->get_next_token();
    Lexer::TokenType currTokenType = currToken.getTokenType();
    if((currTokenType != Lexer::TOK_INT_TYPE) && (currTokenType != Lexer::TOK_FLOAT_TYPE) && (currTokenType != Lexer::TOK_BOOL_TYPE)) {
        print_error("Expected variable type after colon in variable declaration.");
        exit(EXIT_FAILURE);
    }
    std::string tokenType = currToken.token_to_string();
    //If the next token type is not an equals '=', throw an error.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_EQUAL){
        print_error("Expected equals after variable type in variable declaration.");
        exit(EXIT_FAILURE);
    }
    //Get expression.
    ASTExpressionNode *expressionNode = get_expression();
    return new ASTStatementVarDeclare(identifier,tokenType,expressionNode);
}

//To display errors and what line of the input file they are encountered on.
void Parser::print_error(std::string string) {
    const char *new_string = string.c_str();
    std::cerr << "Error on line " << std::to_string(lexer->get_line_number()).c_str() << " - " << new_string << std::endl;
}

ASTStatementNode* Parser::parse_assignment() {
    std::string identifier = currToken.getTokenName(); //Get the identifier.
    //If the next token type is not an equals '=', throw an error.
    currToken = lexer->get_next_token();
    if(currToken.getTokenType() != Lexer::TOK_EQUAL){
        print_error("Expected equals after identifier in assignment statement.");
        exit(EXIT_FAILURE);
    }
    ASTExpressionNode *expressionNode = get_expression(); //Get the expression.
    return new ASTStatementAssignment(identifier,expressionNode);
}

ASTStatementNode* Parser::parse_print_statement(){
    ASTExpressionNode *expressionNode = get_expression(); //Get the expression.
    return new ASTStatementPrint(expressionNode);
}

ASTExpressionNode* Parser::get_expression() {
    ASTExpressionNode* simpleExpression = parse_simple_expression(); //Get a simple expression.
    //If the next token is not relational operator - return just a simple expression.
    if(lexer->check_next_token() != Lexer::TOK_REL_OP)
        return simpleExpression;
    //Otherwise get the next char (operator) and return a binary expression node.
    std::string op = lexer->get_next_token().getTokenName();
    return new ASTExpressionBinary(simpleExpression, get_expression(), op);
}

ASTExpressionNode* Parser::parse_simple_expression() {
    ASTExpressionNode *term = parse_term(); //Get a term.
    //If the next token is not an additive operator, return just term.
    if(lexer->check_next_token() != Lexer::TOK_ADD_OP)
        return term;
    //Otherwise get the next char (operator) and return a binary expression.
    std::string op = lexer->get_next_token().getTokenName();
    return new ASTExpressionBinary(term, get_expression(), op);
}

ASTExpressionNode* Parser::parse_term() {
    ASTExpressionNode *factor = parse_factor(); //Get a factor.
    //If the next token is not an multiplicative operator, return just factor.
    if(lexer->check_next_token() != Lexer::TOK_MULT_OP)
        return factor;
    //Otherwise get the operator and return a binary expression.
    std::string op = lexer->get_next_token().getTokenName();
    return new ASTExpressionBinary(factor, get_expression(), op);
}

ASTExpressionNode* Parser::parse_factor() {
    currToken = lexer->get_next_token();
    switch(currToken.getTokenType()){
        case Lexer::TOK_BOOL_LIT: {
            if (currToken.getTokenName() == "true")
                return new ASTExpressionLiteralBool(true);
            else
                return new ASTExpressionLiteralBool(false);
        }
        case Lexer::TOK_INT_LIT:
            //Int tokens should not have any decimal values - hence can round to obtain int type value.
            return new ASTExpressionLiteralInt(round(currToken.getTokenValue()));
        case Lexer::TOK_FLOAT_LIT:
            return new ASTExpressionLiteralFloat(currToken.getTokenValue());
        case Lexer::TOK_ID: {
            std::string identifier = currToken.getTokenName();
            //Check if next token is '('.
            if (lexer->check_next_token() == Lexer::TOK_LEFT_PAR) {
                //The factor is a Function Call.
                currToken = lexer->get_next_token(); //Skip bracket.
                std::vector<ASTExpressionNode *> expressions; //List of expressions.
                //While the next character is a token, append a new expression to the list.
                while (lexer->check_next_token() != Lexer::TOK_RIGHT_PAR) {
                    ASTExpressionNode* expression = get_expression(); //Get new expression.
                    expressions.push_back(expression); //Add expression to list.
                    if(lexer->check_next_token() == Lexer::TOK_COMMA){
                        currToken = lexer->get_next_token(); //Skip comma.
                    }
                }
                currToken = lexer->get_next_token(); //Skip Right bracket.
                return new ASTExpressionFunctionCall(identifier, expressions);
            }
            //Otherwise the factor is just an identifier.
            return new ASTExpressionIdentifier(identifier);
        }
        case Lexer::TOK_LEFT_PAR: {
            //The factor is a subexpression.
            ASTExpressionNode *expression = get_expression();
            currToken = lexer->get_next_token(); //Get the second bracket.
            if (currToken.getTokenType() != Lexer::TOK_RIGHT_PAR){
                print_error("Expected ')' after expression in a subexpression.");
                exit(EXIT_FAILURE);
            }
            return new ASTExpressionSubExpression(expression);
        }
        case Lexer::TOK_ADD_OP:
        case Lexer::TOK_LOGIC: {
            //Check if the token is '-' or 'not' for a unary expression.
            if (currToken.getTokenName() != "-" || currToken.getTokenName() != "not"){
                print_error("Expected 'not' or '-' before expression in a unary expression.");
                exit(EXIT_FAILURE);
            }
            return new ASTExpressionUnary(currToken.getTokenName(), get_expression());
        }
        default:
            print_error("Unrecognizable factor.");
            exit(EXIT_FAILURE);
    }
}