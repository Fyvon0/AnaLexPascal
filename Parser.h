#ifndef PARSER
#define PARSER

#include <vector>
#include <string>

#include <stdexcept>

#include "Lexer.h"
#include "SymbolTable.h"
#include "ExpressionSolver.h"

class Parser
{
private:
    Lexer lex;
    SymbolTable st;

    ExpressionTokenType toExpressionTokenType(const Token&) throw ();
    ExpressionTokenType toExpressionTokenType(const VariableType&) throw ();
    bool isTypedOrLiteral(const Token&) throw ();

    void throwExpected(TokenType, int, TokenType) throw (runtime_error);
    void throwUndeclared(string, int) throw (runtime_error);
    void throwIncompatibleType(int) throw (runtime_error);
    void throwWtf() throw (runtime_error);

    void compileProgramStart () throw (runtime_error);
    void compileVariableDeclaration () throw (runtime_error);
    void compileProcedureDeclaration () throw (runtime_error);
    void compileFunctionDeclaration () throw (runtime_error);
    void compileCompoundCommand () throw (runtime_error);
    void compileCommand () throw (runtime_error);
    void compileAttr () throw (runtime_error);
    VariableType compileFuncCall () throw (runtime_error);
    VariableType compileTypedSymbol () throw (runtime_error);
    void compileIf () throw (runtime_error);
    void compileWhile () throw (runtime_error);
    void compileWrite () throw (runtime_error);
    void compileRead () throw (runtime_error);
    void compileRelationalExpression() throw (runtime_error);
    void compileArithmeticExpression() throw (runtime_error);
public:
    Parser(string) throw ();
    void compile() throw (runtime_error);
};

#endif
