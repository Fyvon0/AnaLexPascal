#ifndef EXPRESSION_SOLVER_INCLUDED
#define EXPRESSION_SOLVER_INCLUDED

#include <stack>
#include <vector>

#include "Token.h"
#include "Symbol.h"

enum class ExpressionTokenType {
    BOOLEAN,
    INTEGER,

    MULTIPLICATION,
    DIVISION, MODULE,

    SUM,
    SUBTRACTION,

    SMALLER, SMALLER_EQUAL,
    EQUALS, DIFFERENT,
    BIGGER_EQUAL, BIGGER,

    AND,
    OR,

    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS
};

class ExpressionSolver {
    private:
        static vector<vector<ExpressionTokenType>> precedences;

        static bool isOperand(const ExpressionTokenType&) throw ();
        static bool isOperator(const ExpressionTokenType&) throw ();
        static bool isParenthesis(const ExpressionTokenType&) throw ();

        static char getPrecedence(const ExpressionTokenType&, const ExpressionTokenType&) throw ();

        static bool isBalanced(const vector<ExpressionTokenType>&) throw ();

        static vector<ExpressionTokenType> getPostfix(const vector<ExpressionTokenType>&) throw();
        static VariableType getType(const vector<ExpressionTokenType>&) throw (string);
        static VariableType getType(const ExpressionTokenType&) throw ();

        static ExpressionTokenType singleOperation(const ExpressionTokenType&, const ExpressionTokenType&, const ExpressionTokenType&) throw (string);
    public:
        static VariableType evaluate(const vector<ExpressionTokenType>&) throw (string);
};

#endif // EXPRESSION_SOLVER_INCLUDED
