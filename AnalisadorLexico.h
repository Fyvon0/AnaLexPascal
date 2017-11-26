#ifndef ANALEX
#define ANALEX

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Token.h"

using namespace std;

class AnalisadorLexico
{
private:
    vector<Token> tokens; // trocar por forward_list
    //static const regex regex_pattern;
    int iterador;

public:
    AnalisadorLexico(string) throw (string);
    Token tokenAtual() const throw (string);
    Token avancaToken() throw (string);
    Token proximoToken() const throw (string);
    bool temMaisTokens() const throw ();
};

#endif // ANALEX
