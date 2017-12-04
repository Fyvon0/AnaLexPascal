#include <forward_list>
#include <string>
#include <typeinfo>

#include "Parser.h"


string TokenTypeNames[] = {"PROGRAM","VAR","BEGIN","END","IF","WHILE","INTEGER","BOOLEAN","COLON","ATTRIBUTION","SUM",
                           "SUBTRACTION","MULTIPLICATION","DIVISION","MODULE","PROCEDURE","FUNCTION","=","!=",">","<",
                           ">=","<=","NOT","OR","AND","XOR","(",")",".",",",";","WRITE","READ","TRUE","FALSE",
                           "IDENTIFIER","CONSTANT","UNKNOWN"};

Parser::Parser(string path) throw () : lex(path) {}

void Parser::compileProgramStart () throw (string)
{
    Token next = this->lex.nextToken();
    if (next.getType() != TokenType::PROGRAM)
        throw string ("\"PROGRAM\" expected at line " + next.getLine() + " but \"" + TokenTypeNames[(int)next.getType()] + "\" found instead.");
    next = this->lex.nextToken();
    if (next.getType() != TokenType::IDENTIFIER)
        throw string ("IDENTIFIER expected at line " + next.getLine() + " but \"" + TokenTypeNames[(int)next.getType()] + "\" found instead.");
    next = this->lex.nextToken();
    if (next.getType() != TokenType::SEMICOLON)
        throw string("\";\" expected at line " + next.getLine() + "but \"" + TokenTypeNames + "\" found instead");
}
