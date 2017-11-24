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
    vector<Token>::const_iterator iterador;

public:
    AnalisadorLexico(string) throw (string);
    Token leToken() const throw (string);
    Token consomeToken() throw (string);
    bool temMaisTokens() const throw ();
};

#endif // ANALEX
