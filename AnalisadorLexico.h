#ifndef ANALEX
#define ANALEX

#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <iostream>

#include "Token.h"

using namespace std;

class AnalisadorLexico
{
private:
    fstream arq;
    vector<Token> tokens;
    static const regex regex_pattern;

public:
    AnalisadorLexico(string);
    Token proximoToken() const;
    bool temMaisTokens() const;
};

#endif // ANALEX
