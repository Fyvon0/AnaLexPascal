#include "ExpressionSolver.h"

vector<vector<ExpressionTokenType>> ExpressionSolver::precedences = {
    { ExpressionTokenType::MULTIPLICATION, ExpressionTokenType::DIVISION },
    { ExpressionTokenType::SUM, ExpressionTokenType::SUBTRACTION},
    { ExpressionTokenType::SMALLER, ExpressionTokenType::SMALLER_EQUAL, ExpressionTokenType::EQUALS,
        ExpressionTokenType::DIFFERENT, ExpressionTokenType::BIGGER_EQUAL, ExpressionTokenType::BIGGER},
    { ExpressionTokenType::AND },
    { ExpressionTokenType::OR },
    { ExpressionTokenType::LEFT_PARENTHESIS },
    { ExpressionTokenType::RIGHT_PARENTHESIS }
};

bool ExpressionSolver::isOperand(const ExpressionTokenType& t) throw () {
    return t == ExpressionTokenType::BOOLEAN ||
           t == ExpressionTokenType::INTEGER;
}

bool ExpressionSolver::isOperator(const ExpressionTokenType& t) throw () {
    return t == ExpressionTokenType::MULTIPLICATION || t == ExpressionTokenType::DIVISION ||
           t == ExpressionTokenType::SUM || t == ExpressionTokenType::SUBTRACTION ||
           t == ExpressionTokenType::SMALLER || t == ExpressionTokenType::SMALLER_EQUAL ||
           t == ExpressionTokenType::EQUALS || t == ExpressionTokenType::DIFFERENT ||
           t == ExpressionTokenType::BIGGER_EQUAL || t == ExpressionTokenType::BIGGER ||
           t == ExpressionTokenType::AND ||
           t == ExpressionTokenType::OR;
}

bool ExpressionSolver::isParenthesis(const ExpressionTokenType& t) throw () {
    return t == ExpressionTokenType::LEFT_PARENTHESIS || t == ExpressionTokenType::RIGHT_PARENTHESIS;
}

// Precedence of a over b
char ExpressionSolver::getPrecedence(const ExpressionTokenType& a, const ExpressionTokenType& b) throw () {
    char ap = -1,
         bp = -1;
    bool stop = false;
    for (auto i = precedences.cbegin(); !stop && i != precedences.cend(); i++)
        for (auto j = i->cbegin(); !stop && j != i->cend(); j++)
            if (*j == a) {
                ap = i - precedences.cbegin();
                stop = true;
            }

    stop = false;
    for (auto i = precedences.cbegin(); !stop && i != precedences.cend(); i++)
        for (auto j = i->cbegin(); !stop && j != i->cend(); j++)
            if (*j == b) {
                bp = i - precedences.cbegin();
                stop = true;
            }

    return bp - ap;
}

vector<ExpressionTokenType> ExpressionSolver::getPostfix(const vector<ExpressionTokenType>& infix) throw () {
    stack<ExpressionTokenType> s;
    vector<ExpressionTokenType> postfix;

    for(auto it = infix.cbegin(); it != infix.cend(); it++) {
        if (isOperand(*it))
            postfix.push_back(*it);
        else if (*it == ExpressionTokenType::LEFT_PARENTHESIS)
            s.push(ExpressionTokenType::LEFT_PARENTHESIS);
        else if (*it == ExpressionTokenType::RIGHT_PARENTHESIS) {
            ExpressionTokenType t = s.top();
            while (t != ExpressionTokenType::LEFT_PARENTHESIS) {
                postfix.push_back(t);
                s.pop();
                t = s.top();
            }
        }
        else { // Is operator
            ExpressionTokenType t = s.top();
            while (getPrecedence(t, *it) >= 0) {
                postfix.push_back(t);
                s.pop();
                t = s.top();
            }
            s.push(*it);
        }
    }

    // Adds all remaining elements to the finished expression
    while (!s.empty()) {
        if (!isParenthesis(s.top()))
            postfix.push_back(s.top());
        s.pop();
    }

    return postfix;
}

VariableType ExpressionSolver::getType(const vector<ExpressionTokenType>& postfix) throw (string) {

}


VariableType ExpressionSolver::evaluate(const vector<ExpressionTokenType>& infix) throw (string) {
    if (!isBalanced(infix))
        throw string("Expression is not balanced");

    return getType(getPostfix(infix));
}
