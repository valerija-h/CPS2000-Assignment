#ifndef COMPILERSASSIGNMENT_ASTFORMALPARAMS_H
#define COMPILERSASSIGNMENT_ASTFORMALPARAMS_H

//Formal Params for function declaration statement.
class ASTFormalParams{
public:
    std::string identifier;
    std::string type;
    ASTFormalParams(std::string identifier,std::string type);
    void accept(Visitor* v);
};


#endif //COMPILERSASSIGNMENT_ASTFORMALPARAMS_H
