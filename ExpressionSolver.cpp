#include "ExpressionSolver.h"

vector<vector<TokenType>> ExpressionSolver::precedences = {
    { TokenType::MULTIPLICATION, TokenType::DIVISION },
    { TokenType::SUM, TokenType::SUBTRACTION},
    { TokenType::SMALLER, TokenType::SMALLER_EQUAL, TokenType::EQUALS, TokenType::DIFFERENT, TokenType::BIGGER_EQUAL, TokenType::BIGGER},
    { TokenType::AND },
    { TokenType::OR },
    { TokenType::LEFT_PARENTHESIS },
    { TokenType::RIGHT_PARENTHESIS }
};

ExpressionSolver::ExpressionSolver(const vector<TokenType>& exp) throw (string) : exp(exp) {
    for (auto it = this->exp.cbegin(); it != this->exp.cend(); it++)
        if (isError(*it))
            throw string("Expected identifier or operator");
}

bool ExpressionSolver::isOperand(const TokenType& t) throw () {
    return t == TokenType::IDENTIFIER ||
           t == TokenType::INTEGER ||
           t == TokenType::TRUE ||
           t == TokenType::FALSE;
}

bool ExpressionSolver::isOperator(const TokenType& t) throw () {
    return t == TokenType::MULTIPLICATION || t == TokenType::DIVISION ||
           t == TokenType::SUM || t == TokenType::SUBTRACTION ||
           t == TokenType::SMALLER || t == TokenType::SMALLER_EQUAL ||
           t == TokenType::EQUALS || t == TokenType::DIFFERENT ||
           t == TokenType::BIGGER_EQUAL || t == TokenType::BIGGER ||
           t == TokenType::AND ||
           t == TokenType::OR;
}

bool ExpressionSolver::isParenthesis(const TokenType& t) throw () {
    return t == TokenType::LEFT_PARENTHESIS || t == TokenType::RIGHT_PARENTHESIS;
}

bool ExpressionSolver::isError(const TokenType& t) throw () {
    return !isOperand(t) && !isOperator(t) && !isParenthesis(t);
}

// Precedence of a over b
char ExpressionSolver::getPrecedence(const TokenType& a, const TokenType& b) throw () {
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


vector<TokenType> ExpressionSolver::evaluate() throw () {
    stack<TokenType> s;
    vector<TokenType> finalExp;
    for(auto it = this->exp.cbegin(); it != this->exp.cend(); it++) {
        if (isOperand(*it))
            finalExp.push_back(*it);
        else if (*it == TokenType::LEFT_PARENTHESIS)
            s.push(TokenType::LEFT_PARENTHESIS);
        else if (*it == TokenType::RIGHT_PARENTHESIS) {
            TokenType t = s.top();
            while (t != TokenType::LEFT_PARENTHESIS) {
                finalExp.push_back(t);
                s.pop();
                t = s.top();
            }
        }
        else { // Is operator
            TokenType t = s.top();
            while (getPrecedence(t, *it) >= 0) {
                finalExp.push_back(t);
                s.pop();
                t = s.top();
            }
            s.push(*it);
        }
    }

    // Adds all remaining elements to the finished expression
    while (!s.empty()) {
        if (!isParenthesis(s.top()))
            finalExp.push_back(s.top());
        s.pop();
    }

    return finalExp;
}
