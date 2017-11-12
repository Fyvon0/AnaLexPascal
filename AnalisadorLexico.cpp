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

    /*for(regex_iterator<string> i = regex_iterator<string>(tmp.begin(), tmp.end(), AnalisadorLexico::regex_pattern); i != regex_iterator<string>(); ++i ) {
        smatch match = *i;
        cout << match.str();
    }*/

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

//IMPLEMENTAR
Token AnalisadorLexico::proximoToken() const
{

}

bool AnalisadorLexico::temMaisTokens() const
{

}
