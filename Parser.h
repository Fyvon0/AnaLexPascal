#ifndef PARSER
#define PARSER

#include <vector>
#include <string>

#include "Lexer.h"
#include "SymbolTable.h"

class Parser
{
private:
    Lexer lex;
    SymbolTable st;

    void throwExpected(TokenType, int, TokenType) throw (string);

    void compileProgramStart () throw (string);
    void compileVariableDeclaration () throw (string);
    void compileProcedureDeclaration () throw (string);
    //void compileFunctionDeclaration () throw (string);
    void compileCompoundCommand () throw (string);
    void compileCommand () throw (string);
    //void compileAttr () throw (string);
    //void compileProcCall () throw (string);
    //void compileFuncCall () throw (string);
public:
    Parser(string) throw ();
    void compile() throw (string);
};

#endif
