#ifndef PARSER
#define PARSER

#include <list>
#include <string>

#include "Lexer.h"
#include "SymbolTable.h"

class Parser
{
private:
    Lexer lex;
    SymbolTable st;

    void compileProgramStart () throw (string);
public:
    Parser(string) throw ();
};

#endif
