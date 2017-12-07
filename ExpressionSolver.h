#ifndef EXPRESSION_SOLVER_INCLUDED
#define EXPRESSION_SOLVER_INCLUDED

#include <stack>
#include <vector>

#include <stdexcept>

#include "Token.h"
#include "Symbol.h"

using namespace std;

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
    RIGHT_PARENTHESIS,

    UNDEFINED
};

class ExpressionSolver {
    private:
        static vector<vector<ExpressionTokenType>> precedences;

        static bool isOperand(const ExpressionTokenType&) throw ();
        static bool isOperator(const ExpressionTokenType&) throw ();
        static bool isParenthesis(const ExpressionTokenType&) throw ();

        static char getPrecedence(const ExpressionTokenType&, const ExpressionTokenType&) throw ();

        static bool isBalanced(const vector<ExpressionTokenType>&) throw ();

        static vector<ExpressionTokenType> getPostfix(const vector<ExpressionTokenType>&) throw ();
        static VariableType getType(const vector<ExpressionTokenType>&) throw ();
        static VariableType getType(const ExpressionTokenType&) throw ();

        static ExpressionTokenType singleOperation(const ExpressionTokenType&,
                                                   const ExpressionTokenType&,
                                                   const ExpressionTokenType&) throw (runtime_error);
    public:
        static VariableType evaluate(const vector<ExpressionTokenType>&) throw (runtime_error);
};

#endif // EXPRESSION_SOLVER_INCLUDED
