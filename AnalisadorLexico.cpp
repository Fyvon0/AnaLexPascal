#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <iostream>

#include "Token.h"
#include "AnalisadorLexico.h"

using namespace std;

const regex AnalisadorLexico::regex_pattern("(?i)(unit|program|interface|implementation|var|begin|end|if|while|do|break|continue|integer|boolean|mod|procedure|function|div|not|or|and|xor|write|read)(?![A-z]+|[0-9]+)|(:=|:|\+\+|\-\-|\+|\-|\*|\/|\=|\<\>|\<\<|\>\>|\>|\<|\>\=|\<\=|\(|\)|\.|\,|\;)|([0-9]+[A-z]+)|([A-z][A-z0-9]*)|([0-9]+(?![A-z]+))|(\S+)(?-i)");

AnalisadorLexico::AnalisadorLexico(string nomeArq)
{
    this->arq.open(nomeArq.c_str());
    if (!this->arq.is_open())
        throw "Erro ao abrir o arquivo";

    stringstream strstream;
    string tmp;
    strstream << this->arq.rdbuf();
    tmp = strstream.str();

    for(regex_iterator<string> i = regex_iterator<string>(tmp.begin(), tmp.end(), AnalisadorLexico::regex_pattern); i != regex_iterator<string>(); ++i ) {
        smatch match = *i;
        cout << match.str();
    }
}

//IMPLEMENTAR
Token AnalisadorLexico::proximoToken() const
{

}

bool AnalisadorLexico::temMaisTokens() const
{

}
