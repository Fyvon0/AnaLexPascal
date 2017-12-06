#ifndef EXPRESSION_SOLVER_INCLUDED
#define EXPRESSION_SOLVER_INCLUDED

#include <stack>
#include <vector>

#include "Token.h"

class ExpressionSolver {
    private:
        static vector<vector<TokenType>> precedences;
        vector<TokenType> exp;

        static bool isOperand(const TokenType&) throw ();
        static bool isOperator(const TokenType&) throw ();
        static bool isParenthesis(const TokenType&) throw ();
        static bool isError(const TokenType&) throw ();

        static char getPrecedence(const TokenType&, const TokenType&) throw ();
    public:
        ExpressionSolver(const vector<TokenType>&) throw (string);
        vector<TokenType> evaluate() throw ();
};

#endif // EXPRESSION_SOLVER_INCLUDED
