#include "../../include/SymbolTable/symbolTable.h"

SymbolTable::SymbolTable() {
    for(int i=0; i<MAX; i++){
        head[i] = NULL;
    }
}

//Calculates a hashing index for a given identifier.
int SymbolTable::hashingFunction(std::string identifier) {
    int sum = 0;
    for (int i=0; i<identifier.length(); i++){
        sum = sum + identifier[i];
    }
    return (sum % MAX); //Returns a value between 0 and MAX.
}

//Insert a symbol into the hashtable.
void SymbolTable::insert(std::string identifier, std::string declareType, std::string literalType) {
    int index = hashingFunction(identifier);
    Symbol* symbol = new Symbol(identifier, declareType, literalType);
    //If no symbols found in the index.
    if(head[index] == NULL){
        head[index] = symbol;
        return;
    } else {
        //Find the next available position.
        Symbol* start = head[index];
        while(start->next != NULL)
            start = start->next;
        start->next = symbol;
        return;
    }
}

//Lookup a symbol.
Symbol* SymbolTable::lookup(std::string identifier) {
    int index = hashingFunction(identifier);
    Symbol* start = head[index];
    //If not symbols found in the index.
    if(start == NULL){
        return nullptr;
    }
    //Iterate through buckets till symbol with matching identifier is found.
    while(start != NULL){
        if(start->identifier == identifier){
            return start;
        }
        start = start->next;
    }
    return nullptr;
}

//Display info of a symbol.
void SymbolTable::displayInfo(std::string identifier) {
    Symbol* symbol = lookup(identifier);
    symbol->print();
}