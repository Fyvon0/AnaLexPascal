#include <iostream>
#include<string>

#include "Parser.h"
#include "Symbol.h"

using namespace std;

const string TokenTypeNames[] = {"PROGRAM","VAR","BEGIN","END","IF","WHILE","INTEGER","BOOLEAN","COLON","ATTRIBUTION","SUM",
                                 "SUBTRACTION","MULTIPLICATION","DIVISION","MODULE","PROCEDURE","FUNCTION","=","!=",">","<",
                                 ">=","<=","NOT","OR","AND","XOR","(",")",".",",",";","WRITE","READ","TRUE","FALSE",
                                 "IDENTIFIER","CONSTANT","UNKNOWN"};

int main()
{
    cout << "Digite o nome do arquivo: ";
    string nomeArq;
    cin >> nomeArq;

    try {

        Lexer lex (nomeArq);
        while (lex.hasMoreTokens())
            cout << lex.currentToken().getLine() << " - " << TokenTypeNames[(int)lex.currentToken().getType()] << " - " << lex.nextToken().getToken() << endl;

        Parser p(nomeArq);
        p.compile();
        cout << "Compile successful";
    }
    catch (string& s) {
        cout << s;
    }

    return 0;
}
