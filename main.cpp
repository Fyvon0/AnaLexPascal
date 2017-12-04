#include <iostream>
#include<string>
#include "Lexer.h"
#include "Symbol.h"

const string nomeArq("teste.txt");

using namespace std;

int main()
{
    Symbol s(string("Nome"), VariableType::INTEGER, new vector<Symbol>());
    cout << (int)s.getType();
    return 0;
}
