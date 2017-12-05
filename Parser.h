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
public:
    Parser(string) throw ();
    void compile() throw (string);
};

#endif
