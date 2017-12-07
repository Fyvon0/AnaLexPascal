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

static ExpressionTokenType toExpressionTokenType(const TokenType& t) throw () {
    if (t == TokenType::LEFT_PARENTHESIS)
        return ExpressionTokenType::LEFT_PARENTHESIS;
    if (t == TokenType::RIGHT_PARENTHESIS)
        return ExpressionTokenType::RIGHT_PARENTHESIS;

    if (t == TokenType::INTEGER)
        return ExpressionTokenType::INTEGER;
    if (t == TokenType::TRUE || t == TokenType::FALSE)
        return ExpressionTokenType::BOOLEAN;

    if (t == TokenType::MULTIPLICATION)
        return ExpressionTokenType::MULTIPLICATION;
    if (t == TokenType::DIVISION)
        return ExpressionTokenType::DIVISION;
    if (t == TokenType::MODULE)
        return ExpressionTokenType::MODULE;
    if (t == TokenType::SUM)
        return ExpressionTokenType::SUM;
    if (t == TokenType::SUBTRACTION)
        return ExpressionTokenType::SUBTRACTION;

    if (t == TokenType::SMALLER)
        return ExpressionTokenType::SMALLER;
    if (t == TokenType::SMALLER_EQUAL)
        return ExpressionTokenType::SMALLER_EQUAL;
    if (t == TokenType::EQUALS)
        return ExpressionTokenType::EQUALS;
    if (t == TokenType::DIFFERENT)
        return ExpressionTokenType::DIFFERENT;
    if (t == TokenType::BIGGER_EQUAL)
        return ExpressionTokenType::BIGGER_EQUAL;
    if (t == TokenType::BIGGER)
        return ExpressionTokenType::BIGGER;
}

int main()
{
    cout << "Digite o nome do arquivo: ";
    string nomeArq;
    cin >> nomeArq;

    try {
        Lexer lex (nomeArq);

        vector<TokenType> tokens;
        vector<ExpressionTokenType> expTokens;
        while (lex.hasMoreTokens())
            tokens.push_back(lex.nextToken().getType());

        for (auto it=tokens.cbegin(); it != tokens.cend(); it++) {
            cout << TokenTypeNames[(int)*it] << " ";
            expTokens.push_back(toExpressionTokenType(*it));
        }

        VariableType v(ExpressionSolver::evaluate(expTokens));

        cout << endl;
        cout << ((v == VariableType::BOOLEAN) ? "BOOL" : "INT");

        /* Parser p(nomeArq);
        p.compile();
        cout << "Compile successful"; */
    }
    catch (string& s) {
        cout << s;
    }

    return 0;
}
