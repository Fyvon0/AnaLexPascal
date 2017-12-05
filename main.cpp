#include <iostream>
#include<string>

#include "Parser.h"
#include "Symbol.h"

using namespace std;

int main()
{
    cout << "Digite o nome do arquivo: ";
    string nomeArq;
    cin >> nomeArq;

    try {
        Parser p(nomeArq);
        p.compile();
    }
    catch (string& s) {
        cout << s;
    }

    return 0;
}
