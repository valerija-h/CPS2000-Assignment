#ifndef COMPILERSASSIGNMENT_SYMBOLTABLE_H
#define COMPILERSASSIGNMENT_SYMBOLTABLE_H

#define MAX 10 //Hashtable size.

//A single symbol object.
struct Symbol {
    std::string identifier;
    std::string declareType; //function or variable.
    std::string literalType; //int, bool or float.
    struct Symbol *next;
public:
    std::vector<std::string> functionParmTypes; //stores the parameters of a function declaration.
    Symbol(){
        next = nullptr;
    }
    Symbol(std::string identifier, std::string declareType, std::string literalType){
        this->identifier = identifier;
        this->declareType = declareType;
        this->literalType = literalType;
    }
    //Displaying contents of one symbol.
    void print(){
        std::cout << "Identifier's Name:" << identifier << std::endl;
        std::cout << "Declaration Type:" << declareType <<std::endl;
        std::cout << "Literal Type: " << literalType << std::endl;
    }
    //Getters.
    std::string getName(){ return identifier;}
    std::string getDeclareType(){ return declareType;}
    std::string getLiteralType(){ return literalType;}
};

//Symbol table implemented using a hash table.
class SymbolTable {
    Symbol* head[MAX]; //An array of pointers to symbols.
public:
    SymbolTable();
    void insert(std::string identifier, std::string declareType, std::string literalType); //Insert a new symbol.
    Symbol* lookup(std::string identifier); //Look up a symbol by identifier.
    int hashingFunction(std::string identifier); //Return an index for a given identifier.
    void displayInfo(std::string identifier); //Display info of a symbol.
};

#endif //COMPILERSASSIGNMENT_SYMBOLTABLE_H
