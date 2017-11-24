#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Token.h"
#include "AnalisadorLexico.h"

#define ehIgnoravel(c) (((c)=='\n')||((c)=='\t')||((c)==' '))?true:false

using namespace std;

//const regex AnalisadorLexico::regex_pattern("(?i)(unit|program|interface|implementation|var|begin|end|if|while|do|break|continue|integer|boolean|mod|procedure|function|div|not|or|and|xor|write|read)(?![A-z]+|[0-9]+)|(:=|:|\+\+|\-\-|\+|\-|\*|\/|\=|\<\>|\<\<|\>\>|\>|\<|\>\=|\<\=|\(|\)|\.|\,|\;)|([0-9]+[A-z]+)|([A-z][A-z0-9]*)|([0-9]+(?![A-z]+))|(\S+)(?-i)");

/*
AnalisadorLexico::AnalisadorLexico(string nomeArq)
{
    this->arq.open(nomeArq.c_str());
    if (!this->arq.is_open())
        throw "Erro ao abrir o arquivo";

    stringstream strstream;
    string tmp;
    strstream << this->arq.rdbuf();
    tmp = strstream.str();

    try {
        //regex re("\\w+");
        sregex_iterator seguinte(tmp.begin(), tmp.end(), AnalisadorLexico::regex_pattern);
        sregex_iterator fim;
        while (seguinte != fim) {
            smatch match = *seguinte;
            cout << "0 - " << string(match[0]) << "\n";
            cout << "1 - " << string(match[1]) << "\n";
            cout << "2 - " << string(match[2]) << "\n";
            cout << "3 - " << string(match[3]) << "\n";
            cout << "4 - " << string(match[4]) << "\n";
            cout << "5 - " << string(match[5]) << "\n";
            cout << "6 - " << string(match[6]) << "\n";
            cout << match.str() << "\n";
            seguinte++;
        }
    } catch (regex_error& e) {
        // Syntax error in the regular expression
    } catch (...) {
        //Vai saber
    }
}
*/
// https://docs.microsoft.com/pt-br/cpp/ide/xml-documentation-visual-cpp - Documentação
/// <summary> Lê o arquivo indicado e guarda seus dados para que depois sejam iterados
///</summary>
AnalisadorLexico::AnalisadorLexico(string nomeArq) throw (string)
{
    ifstream arq(nomeArq);
    if (arq.fail())
        throw string("Nao foi possivel abrir o arquivo indicado");

    char c = tolower(arq.get());
    string word;

    while (arq.good())
    {
        if (isspace(c))
        {
            Token newToken(word);
            this -> tokens.push_back(newToken);
            word.clear();
        }
        else
            word += c;

        c = tolower(arq.get());
    }

    arq.close();
    this -> iterador = tokens.cbegin();
}

//IMPLEMENTAR
Token AnalisadorLexico::leToken() const throw (string)
{
    if (!this -> temMaisTokens())
        throw string("Não existem mais tokens a serem buscados");
    Token t = *(this -> iterador);
    return t;
}

Token AnalisadorLexico::consomeToken() throw (string)
{
    if (!this -> temMaisTokens())
        throw string("Não existem mais tokens a serem buscados");
    Token t = *(this -> iterador);
    ++(this -> iterador);
    return t;
}

bool AnalisadorLexico::temMaisTokens() const throw ()
{
    return this -> iterador != this -> tokens.cend();
}
