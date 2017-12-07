#include <iostream>
#include<string>

#include "Parser.h"
#include "Symbol.h"
#include "ExpressionSolver.h"

using namespace std;

const string TokenTypeNames[] = {"PROGRAM","VAR","BEGIN","END","IF","THEN","ELSE","WHILE","DO","REPEAT","UNTIL","INTEGER","BOOLEAN","COLON","ATTRIBUTION","SUM",
                                 "SUBTRACTION","MULTIPLICATION","DIVISION","MODULE","PROCEDURE","FUNCTION","=","!=",">","<",
                                 ">=","<=","NOT","OR","AND","XOR","(",")",".",",",";","WRITE","READ","TRUE","FALSE",
                                 "IDENTIFIER","CONSTANT","UNKNOWN"};

int main()
{
    cout << "Digite o nome do arquivo: ";
    string nomeArq;
    cin >> nomeArq;

    /*
    Lexer lex (nomeArq);
    while (lex.hasMoreTokens())
        cout << lex.currentToken().getLine() << ": " << TokenTypeNames[(int)lex.currentToken().getType()] << " - " <<  lex.nextToken().getToken() << endl;
    */


    try {
        Parser p(nomeArq);
        p.compile();
        cout << "Compile successful";
    }
    catch (runtime_error e) {
        cout << e.what();
    }
    catch (...) {
        cout << "O cheiro de merda eh forte";
    }

    return 0;
}
