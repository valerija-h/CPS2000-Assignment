#include "../include/semanticAnalysisVisitor.h"

SemanticAnalysisVisitor::SemanticAnalysisVisitor() {}

void SemanticAnalysisVisitor::visit(ASTProgramNode* node){
    addTable(); //Add a new symbol table for this scope.
    for(auto &statement : node->statements){
        statement->accept(this);
    }
    removeLastTable();
}

void SemanticAnalysisVisitor::visit(ASTStatementNode *node){}

void SemanticAnalysisVisitor::visit(ASTStatementVarDeclare *node){
    //Check if it was previously declared.
    if(checkInTables(node->identifier) == nullptr){
        //Add variable declaration to symbol table.
        SymbolTable* currentScope = getLastTable();
        currentScope->insert(node->identifier,"variable",node->type);
        std::string prevLiteralType = currentLiteralType;
        currentLiteralType = node->type; //Expression has to be of the current literal type.
            node->expression->accept(this); //Check expression.
        currentLiteralType = prevLiteralType;
    } else {
        //Double variable declaration.
        std::cerr << "Semantic Error - variable \"" << node->identifier << "\" already declared in previous scope."<< std::endl;
    }
}

void SemanticAnalysisVisitor::visit(ASTStatementAssignment *node){
    //Check the identifier exists in symbol table.
    if(checkInTables(node->identifier) != nullptr){
        //Checking for type mismatch.
        std::string prevLiteralType = currentLiteralType;
        currentLiteralType = checkInTables(node->identifier)->getLiteralType(); //Expression has to be of the current literal type.
            node->expression->accept(this); //Check expression.
        currentLiteralType = prevLiteralType;
    } else {
        std::cerr << "Semantic Error in assignment of \"" << node->identifier << "\" - was not declared in previous scopes."<< std::endl;
    }
}

void SemanticAnalysisVisitor::visit(ASTStatementPrint *node){
    //Binary Checking
    std::string prevLiteralType = currentLiteralType;
    currentLiteralType = "";
    node->expression->accept(this); //Check expression.
    currentLiteralType = prevLiteralType;
}

void SemanticAnalysisVisitor::visit(ASTStatementBlock *node){
    for(auto &statement : node->statements){
        statement->accept(this);
    }
}

void SemanticAnalysisVisitor::visit(ASTStatementIf *node){
    //Binary checking.
    std::string prevLiteralType = currentLiteralType;
    currentLiteralType = "";
    node->expression->accept(this); //Check expression.
    currentLiteralType = prevLiteralType;
    addTable();
    node->ifBlock->accept(this);
    removeLastTable();
    //If the else block exists.
    if(node->elseBlock){
        addTable();
        node->elseBlock->accept(this);
        removeLastTable();
    }
}

void SemanticAnalysisVisitor::visit(ASTStatementFor *node){
    addTable(); ////Create a new scope for the for loop block.
    SymbolTable* currentScope = getLastTable();
    //If there is a variable declaration, insert it into the current scope.
    if(node->varDeclare){
        node->varDeclare->accept(this);
    }
    //Check if expression is valid semantically with binary checking.
    std::string prevLiteralType = currentLiteralType;
    currentLiteralType = "";
    node->expression->accept(this);
    currentLiteralType = prevLiteralType;
    //Check if the assignment is valid.
    if(node->assignment){
        node->assignment->accept(this);
    }
    node->block->accept(this);
    removeLastTable(); ////Remove scope.
}

void SemanticAnalysisVisitor::visit(ASTStatementReturn *node){
    node->expression->accept(this); //Check expression.
}

void SemanticAnalysisVisitor::visit(ASTFormalParams *node){
    //Declare all formal params in the current scope.
    SymbolTable* currentScope = getLastTable();
    currentScope->insert(node->identifier,"variable",node->type);
}

void SemanticAnalysisVisitor::visit(ASTStatementFunctionDeclare* node){
    //Function declarations should be global.
    if(symbolTables.size()>1){
        std::cerr << "Semantic Error - function declaration \"" << node->identifier << "\" is not global."<< std::endl;
    } else {
        //Check for double declaration.
        if(checkInTables(node->identifier) == nullptr){
            //Type mismatch.
            std::string prevLiteralType = currentLiteralType;
            currentLiteralType = node->type;
            //Add the function declaration to the current scope.
            SymbolTable* currentScope = getLastTable();
            currentScope->insert(node->identifier,"function",node->type);
            addTable(); ////Create a new scope for the function block.
            currentScope = getLastTable();
            //Add the function formal params to new scope and call the block.
            for(auto &formalParam : node->formalParams){
                formalParam->accept(this);
                checkInTables(node->identifier)->functionParmTypes.push_back(formalParam->type);
            }
            node->block->accept(this);
            removeLastTable(); ////Remove scope.
            currentLiteralType = prevLiteralType;
        } else {
            std::cerr << "Semantic Error - function \"" << node->identifier << "\" was declared twice."<< std::endl;
        }
    }
}

void SemanticAnalysisVisitor::visit(ASTExpressionNode *node){}

void SemanticAnalysisVisitor::visit(ASTExpressionSubExpression *node){
    node->expression->accept(this); //Check expression.
}

void SemanticAnalysisVisitor::visit(ASTExpressionUnary *node){
    node->expression->accept(this); //Check expression.
}

void SemanticAnalysisVisitor::visit(ASTExpressionLiteralBool *node){
    if(enableBinaryChecking && binaryLiteralType == ""){
        binaryLiteralType = "TOK_BOOL_TYPE";
    } else if (enableBinaryChecking){
        if(binaryLiteralType !=  "TOK_BOOL_TYPE"){
            std::cerr << "Semantic Error - type mismatch: "<< node->value << std::endl;
        }
    } else {
        if(currentLiteralType != "TOK_BOOL_TYPE"){
            std::cerr << "Semantic Error - type mismatch: "<< node->value << std::endl;
        }
    }
}

void SemanticAnalysisVisitor::visit(ASTExpressionLiteralFloat *node){
    if(enableBinaryChecking && binaryLiteralType == ""){
        binaryLiteralType = "TOK_FLOAT_TYPE";
    } else if (enableBinaryChecking){
        if(binaryLiteralType !=  "TOK_FLOAT_TYPE"){
            std::cerr << "Semantic Error - type mismatch: "<< node->value << std::endl;
        }
    } else {
        if(currentLiteralType != "TOK_FLOAT_TYPE"){
            std::cerr << "Semantic Error - type mismatch: "<< node->value << std::endl;
        }
    }
}

void SemanticAnalysisVisitor::visit(ASTExpressionLiteralInt *node){
    if(enableBinaryChecking && binaryLiteralType == ""){
        binaryLiteralType = "TOK_INT_TYPE";
    } else if (enableBinaryChecking){
        if(binaryLiteralType !=  "TOK_INT_TYPE"){
            std::cerr << "Semantic Error - type mismatch: "<< node->value << std::endl;
        }
    } else {
        if(currentLiteralType != "TOK_INT_TYPE"){
            std::cerr << "Semantic Error - type mismatch: "<< node->value << std::endl;
        }
    }
}

void SemanticAnalysisVisitor::visit(ASTExpressionIdentifier *node){
    //Check if it was declared and that the type matches.
    if(checkInTables(node->identifier) == nullptr){
        std::cerr << "Semantic Error - identifier \""<< node->identifier <<"\" was not declared."<< std::endl;
    } else {
        if(enableBinaryChecking && binaryLiteralType == ""){
            binaryLiteralType = checkInTables(node->identifier)->getLiteralType();
        } else if (enableBinaryChecking){
            if(binaryLiteralType !=  checkInTables(node->identifier)->getLiteralType()){
                std::cerr << "Semantic Error - type mismatch for identifier: "<< node->identifier << std::endl;
            }
        } else {
            if(checkInTables(node->identifier)->getLiteralType() != currentLiteralType){
                std::cerr << "Semantic Error - type mismatch for identifier: " << node->identifier << std::endl;
            }
        }
    }
}

void SemanticAnalysisVisitor::visit(ASTExpressionFunctionCall *node){
    //Check if function was previously declared.
    if(checkInTables(node->identifier) == nullptr){
        std::cerr << "Semantic Error - function \"" << node->identifier << "\" was called without declaration."<< std::endl;
    } else {
        //Check if param types are matching.
        Symbol* functionDeclaration = checkInTables(node->identifier);
        //Check the length of params is the same and the type.
        if(node->actualParams.size() != functionDeclaration->functionParmTypes.size()) {
            std::cerr << "Semantic Error - function call \"" << node->identifier
                      << "\" actual and formal parameters value amount mismatch." << std::endl;
        }
    }
}

void SemanticAnalysisVisitor::visit(ASTExpressionBinary *node){
    if(currentLiteralType == "" && symbolTables.size() > 1){
        enableBinaryChecking = true;
        node->LHS->accept(this);
        node->RHS->accept(this);
        binaryLiteralType = "";
        enableBinaryChecking = false;
    } else {
        node->LHS->accept(this);
        node->RHS->accept(this);
    }
}

//Symbol Table List Functions.
SymbolTable* SemanticAnalysisVisitor::getLastTable() {
    return symbolTables.back();
}

void SemanticAnalysisVisitor::addTable() {
    symbolTables.push_back(new SymbolTable());
}

void SemanticAnalysisVisitor::removeLastTable() {
    SymbolTable* toRemove = getLastTable();
    symbolTables.pop_back();
    delete(toRemove);
}

Symbol* SemanticAnalysisVisitor::checkInTables(std::string identifier) {
    //From last symbol table goes backwards in list.
    for(int i=(symbolTables.size() - 1); i >= 0; i--){
        if(symbolTables[i]->lookup(identifier) != nullptr){
            return symbolTables[i]->lookup(identifier);
        }
    }
    return nullptr;
}
