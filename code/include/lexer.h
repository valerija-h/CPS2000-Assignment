#ifndef COMPILERSASSIGNMENT_LEXER_H
#define COMPILERSASSIGNMENT_LEXER_H

#define STATE_NO 20 //The number of states.
#define CLASSIFIER_NO 14 //The number of classifiers.

#include <iostream>
#include <string>
#include <fstream>
#include <stack>

class Lexer{
public:
    /* Types of Tokens that can be used */
    enum TokenType {
        //1 - Parenthesis and special tokens.
        //2 - Operators and punctuation and =.
        //3 - Literals and literal types.
        //4 - Identifier, Variable declare, Print, Return, Function Declare
        //5 - If statement, else statement, for loop, logic, comments, printable.
                TOK_EOF = 1, TOK_ERROR = 2, TOK_LEFT_PAR = 3, TOK_RIGHT_PAR = 4, TOK_LEFT_CURLY = 5, TOK_RIGHT_CURLY = 6,
        TOK_MULT_OP = 7, TOK_ADD_OP = 8, TOK_REL_OP = 9, TOK_COMMA = 10, TOK_COLON = 11, TOK_SEMICOLON = 12, TOK_EQUAL = 13,
        TOK_BOOL_LIT = 14, TOK_FLOAT_LIT = 15, TOK_INT_LIT = 16, TOK_BOOL_TYPE = 17, TOK_FLOAT_TYPE = 18, TOK_INT_TYPE = 19,
        TOK_ID = 20, TOK_VAR_DECLARE = 21, TOK_PRINT = 22, TOK_RETURN = 23, TOK_FUN_DECLARE = 24,
        TOK_IF = 25, TOK_ELSE = 26, TOK_FOR = 27, TOK_LOGIC = 28, TOK_COMMENT = 29
    };
    enum Classifier {
        CLASS_EOF = 0, CLASS_BIG_SMALL = 1, CLASS_EQUALS = 2, CLASS_EXCLAMATION = 3, CLASS_ADD_SUB = 4, CLASS_MULT = 5,
        CLASS_DIV = 6, CLASS_NEW_LINE = 7, CLASS_PUNCT = 8, CLASS_LETTER = 9, CLASS_DIGIT = 10,
        CLASS_FULL_STOP = 11, CLASS_UNDERSCORE = 12, CLASS_OTHERS = 13
    };
    /* */
    enum State {
        S00 = 0, S01 = 1, S02 = 2, S03 = 3, S04 = 4, S05 = 5, S06 = 6, S07 = 7, S08 = 8, S09 = 9, S10 = 10, S11 = 11,
        S12 = 12, S13 = 13, S14 = 14, S15 = 15, S16 = 16, S17 = 17, S18 = 18, SERR = 19
    };
    //The transition table for the lexer.
    State transitionTable[STATE_NO][CLASSIFIER_NO] = {{S01,S02,S04,S05,S06,S07,S08,S00,S11,S12,S13,SERR,SERR,SERR},
                                                      {SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR},
                                                      {SERR,SERR,S03,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR},
                                                      {SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR},
                                                      {SERR,SERR,S03,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR},
                                                      {SERR,SERR,S03,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR},
                                                      {SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR},
                                                      {SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR},
                                                      {SERR,SERR,SERR,SERR,SERR,S16,S09,SERR,SERR,SERR,SERR,SERR,SERR,SERR},
                                                      {SERR,S09,S09,S09,S09,S09,S09,S10,S09,S09,S09,S09,S09,S09},
                                                      {SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR},
                                                      {SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR},
                                                      {SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,S12,S12,SERR,S12,SERR},
                                                      {SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,S13,S14,SERR,SERR},
                                                      {SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,S15,SERR,SERR,SERR},
                                                      {SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,S15,SERR,SERR,SERR},
                                                      {SERR,S16,S16,S16,S16,S17,S16,S16,S16,S16,S16,S16,S16,S16},
                                                      {SERR,S16,S16,S16,S16,S16,S18,S16,S16,S16,S16,S16,S16,S16},
                                                      {SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR},
                                                      {SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR,SERR}}; //Error State.

    struct Token{
    private:
        TokenType tokenType; //The token type.
        std::string tokenName; //For storing string values.
        float tokenValue; //For number type tokens.

    public:
        explicit Token(TokenType tokenType){
            this->tokenType = tokenType;
        }

        Token(TokenType tokenType, const std::string &tokenName){
            this->tokenType = tokenType;
            this->tokenName = tokenName;
        }

        Token(TokenType tokenType, float tokenValue){
            this->tokenType = tokenType;
            this->tokenValue = tokenValue;
        }

        Token(TokenType tokenType, const std::string &tokenName, float tokenValue){
            this->tokenType = tokenType;
            this->tokenName = tokenName;
            this->tokenValue = tokenValue;
        }

        //Getters.
        TokenType getTokenType(){ return tokenType; }
        std::string getTokenName(){ return tokenName; }
        float getTokenValue(){ return tokenValue; }

        //Returns the string of the tokenType.
        std::string token_to_string(){
            switch(this->tokenType){
                case TOK_EOF: return "TOK_EOF";
                case TOK_LEFT_PAR: return "TOK_LEFT_PAR";
                case TOK_RIGHT_PAR: return "TOK_RIGHT_PAR";
                case TOK_LEFT_CURLY: return "TOK_LEFT_CURLY";
                case TOK_RIGHT_CURLY: return "TOK_RIGHT_CURLY";
                case TOK_MULT_OP: return "TOK_MULT_OP";
                case TOK_ADD_OP: return "TOK_ADD_OP";
                case TOK_REL_OP: return "TOK_REL_OP";
                case TOK_COMMA: return "TOK_COMMA";
                case TOK_COLON: return "TOK_COLON";
                case TOK_SEMICOLON: return "TOK_SEMICOLON";
                case TOK_EQUAL: return "TOK_EQUAL";
                case TOK_BOOL_LIT: return "TOK_BOOL_LIT";
                case TOK_FLOAT_LIT: return "TOK_FLOAT_LIT";
                case TOK_INT_LIT: return "TOK_INT_LIT";
                case TOK_BOOL_TYPE: return "TOK_BOOL_TYPE";
                case TOK_FLOAT_TYPE: return "TOK_FLOAT_TYPE";
                case TOK_INT_TYPE: return "TOK_INT_TYPE";
                case TOK_ID: return "TOK_ID";
                case TOK_VAR_DECLARE: return "TOK_VAR_DECLARE";
                case TOK_PRINT: return "TOK_PRINT";
                case TOK_RETURN: return "TOK_RETURN";
                case TOK_FUN_DECLARE: return "TOK_FUN_DECLARE";
                case TOK_IF: return "TOK_IF";
                case TOK_ELSE: return "TOK_ELSE";
                case TOK_FOR: return "TOK_FOR";
                case TOK_LOGIC: return "TOK_LOGIC";
                case TOK_COMMENT: return "TOK_COMMENT";
                case TOK_ERROR: return "Error";
                default: return "Error";
            }
        }
    };

    /* ------- Lexer Variables ----- */
    std::string inputProgram;
    int charIndex;
    int lineNumber;

    /* ------- Functions -------- */
    Lexer(const std::string &fileName);
    void get_all_tokens();
    Token get_token_type(State state, std::string lexeme); //Returns a tokenType for a given state and lexeme.
    Token get_next_token();
    TokenType check_next_token();
    Token check_punctuation(State state, std::string lexeme);
    Token check_letters(State state, std::string lexeme);

    //Return a classifier for a given character c.
    int find_classifier(char c);
    //Checks whether a state is accepting or not.
    bool is_final_state(State state);
    int get_line_number();
};

#endif //COMPILERSASSIGNMENT_LEXER_H
