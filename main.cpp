#include <iostream>
#include<string>
#include "AnalisadorLexico.h"

const string nomeArq("teste.txt");

using namespace std;

int main()
{
    AnalisadorLexico a(nomeArq);

    while (a.temMaisTokens())
    {
        cout << a.tokenAtual().getLinha() << " - " << (int)a.tokenAtual().getTipo() << " - " << a.tokenAtual().getToken() << "\n";
        a.avancaToken();
    }
    return 0;
}
