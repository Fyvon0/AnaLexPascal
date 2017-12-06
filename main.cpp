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

    try {
        Lexer lex (nomeArq);

        vector<TokenType> tokens;
        while (lex.hasMoreTokens())
            tokens.push_back(lex.nextToken().getType());

        for (auto it=tokens.cbegin(); it != tokens.cend(); it++)
            cout << TokenTypeNames[(int)*it] << " ";

        vector<TokenType> v(ExpressionSolver::evaluate(tokens));

        cout << endl;
        for (auto it=v.cbegin(); it != v.cend(); it++)
            cout << TokenTypeNames[(int)*it] << " ";

        /* Parser p(nomeArq);
        p.compile();
        cout << "Compile successful"; */
    }
    catch (string& s) {
        cout << s;
    }

    return 0;
}
