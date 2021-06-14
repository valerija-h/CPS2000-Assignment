#include "../include/lexer.h"

void Lexer::get_all_tokens() {
    Lexer::Token nextToken = Token(TOK_ERROR);
    while(nextToken.token_to_string() != "TOK_EOF"){
        nextToken = Lexer::get_next_token();
        std::cout << nextToken.token_to_string() << std::endl;
    }
}

Lexer::TokenType Lexer::check_next_token() {
    int prevCharIndex = this->charIndex; //Stores the previous char index.
    TokenType type = get_next_token().getTokenType(); //Gets the next token.
    this->charIndex = prevCharIndex; //Resets to previous char index.
    return type;
}

Lexer::Lexer(const std::string &fileName) {
    std::string inputString; //Where the lines of the program are stored.
    //Open a file called fileName.
    std::ifstream file(fileName);
    if(!file){
        std::cout << "Error - Cannot open input file.\n" << std::endl;
    } else {
        //Reading each line from the file.
        std::string line;
        while(std::getline(file, line)){
            inputString.append(line + "\n");
        }
    }
    //Read each line from and append it into a string called inputProgram.
    //Set charIndex to 0 and line number to 1.
    this->inputProgram = inputString;
    this->charIndex = 0;
    this->lineNumber = 1;
}

Lexer::Token Lexer::get_next_token(){
    State currentState = S00; //Starting state.
    std::stack<State> stack;
    stack.push(SERR); //Push the error state onto stack.
    std::string lexeme = "";
    char thisChar;

    //Scanning loop - get each character until an error state is reached.
    while(currentState != SERR){
        thisChar = inputProgram[charIndex];
        charIndex++;
        //Skip new lines and empty characters.
        while(lexeme.length() == 0 && (thisChar == '\n' || thisChar == '\r'|| thisChar == ' ')){
            if(thisChar == '\n'){ lineNumber++; }
            thisChar = inputProgram[charIndex];
            charIndex++;
        }
        //Add the current character to the lexeme.
        lexeme += thisChar;
        if(is_final_state(currentState))
            stack.empty();
        stack.push(currentState);
        currentState = transitionTable[currentState][find_classifier(thisChar)];
    }
    //Rollback loop - go back till you find an accepting state or non-error state.
    while(!is_final_state(currentState) && currentState == SERR){
        currentState = stack.top();
        stack.pop();
        lexeme.pop_back();
        charIndex--;
    }

    //Report result.
    if(is_final_state(currentState)){
        Token token = get_token_type(currentState,lexeme);
        //Skip comments.
        if(token.getTokenType() == TOK_COMMENT){
            return get_next_token();
        }
        return token;
    }
    else{
        std::cerr << "Error - unrecognized token on line " << lineNumber << "." <<std::endl;
        exit(EXIT_FAILURE);
    }
}

//Create an appropriate token with a given.
Lexer::Token Lexer::get_token_type(State state, std::string lexeme){
    if(state == S01)
        return Lexer::Token(TOK_EOF);
    //Relational Operators.
    if(state == S02 || state == S03)
        return Lexer::Token(TOK_REL_OP, lexeme);
    if(state == S04)
        return Lexer::Token(TOK_EQUAL);
    //Additive Operators.
    if(state == S06)
        return Lexer::Token(TOK_ADD_OP, lexeme);
    //Multiplicative Operators.
    if(state == S07 || state == S08)
        return Lexer::Token(TOK_MULT_OP, lexeme);
    if(state == S10){
        lineNumber++;
        return Lexer::Token(TOK_COMMENT);
    }
    if(state == S18){
        return Lexer::Token(TOK_COMMENT);
    }
    //Check the punctuation.
    if(state == S11)
        return check_punctuation(state, lexeme);
    //Check if literal or keyword.
    if(state == S12)
        return check_letters(state, lexeme);
    //Check if float or int.
    if(state == S13)
        return Lexer::Token(TOK_INT_LIT, stod(lexeme));
    if(state == S15)
        return Lexer::Token(TOK_FLOAT_LIT, stod(lexeme));
    return Lexer::Token(TOK_ERROR); //Error.
}

Lexer::Token Lexer::check_punctuation(State state, std::string lexeme){
    if(lexeme == "}")
        return Lexer::Token(TOK_RIGHT_CURLY);
    if(lexeme == "{")
        return Lexer::Token(TOK_LEFT_CURLY);
    if(lexeme == "(")
        return Lexer::Token(TOK_LEFT_PAR);
    if(lexeme == ")")
        return Lexer::Token(TOK_RIGHT_PAR);
    if(lexeme == ":")
        return Lexer::Token(TOK_COLON);
    if(lexeme == ";")
        return Lexer::Token(TOK_SEMICOLON);
    if(lexeme == ",")
        return Lexer::Token(TOK_COMMA);
    return Lexer::Token(TOK_COMMA);    
}

Lexer::Token Lexer::check_letters(State state, std::string lexeme){
    //If it is bool or logic, return the TokenType + ID.
    if(lexeme == "or" || lexeme == "and" || lexeme == "not"){
        return Token(TOK_LOGIC, lexeme);
    }
    if(lexeme == "true" || lexeme == "false"){
        return Token(TOK_BOOL_LIT, lexeme);
    }
    //Make a list of keywords and their token types.
    std::string keywords[] = { "int", "float", "bool", "var", "return", "print", "if", "else", "for", "fn" };
    Lexer::TokenType tokenTypes[] = {TOK_INT_TYPE, TOK_FLOAT_TYPE, TOK_BOOL_TYPE,
                      TOK_VAR_DECLARE, TOK_RETURN, TOK_PRINT, TOK_IF, TOK_ELSE, TOK_FOR, TOK_FUN_DECLARE};
    //Check if lexeme is a keyword.
    for(int i=0; i<10; i++){
        //If lexeme and keyword matches.
        if(!lexeme.compare(keywords[i])){
            return Token(tokenTypes[i]);
        }
    }
    //Otherwise it is an identifier.
    return Token(TOK_ID, lexeme);
}

bool Lexer::is_final_state(State state){
    switch (state){
        case S01:
        case S02:
        case S03:
        case S04:
        case S06:
        case S07:
        case S08:
        case S10:
        case S11:
        case S12:
        case S13:
        case S15:
        case S18:
            return true;
        default:
            return false;
    }
}

int Lexer::find_classifier(char c){
    if(c == EOF || c == '\0')
        return CLASS_EOF;
    if(c == '<' || c == '>')
        return CLASS_BIG_SMALL;
    if(c == '=')
        return CLASS_EQUALS;
    if(c == '!')
        return CLASS_EXCLAMATION;
    if(c == '+' || c == '-')
        return CLASS_ADD_SUB;
    if(c == '*')
        return CLASS_MULT;
    if(c == '/')
        return CLASS_DIV;
    if(c == '\n' || c == '\r')
        return CLASS_NEW_LINE;
    if(c == '.')
        return CLASS_FULL_STOP;
    if(c == '_')
        return CLASS_UNDERSCORE;
    if(c == '}' || c == '{' || c == ')' || c == '(')
        return CLASS_PUNCT;
    if(c == ':' || c == ';' || c == ',')
        return CLASS_PUNCT;
    if(isdigit(c))
        return CLASS_DIGIT;
    if(isalpha(c))
        return CLASS_LETTER;
    return CLASS_OTHERS;
}

int Lexer::get_line_number() { return lineNumber;}