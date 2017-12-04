#include <vector>
#include <string>

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
        throw string ("\"" + TokenTypeNames[TokenType::PROGRAM] + "\" expected at line " + next.getLine() + " but \"" + TokenTypeNames[(int)next.getType()] + "\" found instead.");
    next = this->lex.nextToken();
    if (next.getType() != TokenType::IDENTIFIER)
        throw string ("\"" + TokenTypeNames[TokenType::IDENTIFIER] + "\" expected at line " + next.getLine() + " but \"" + TokenTypeNames[(int)next.getType()] + "\" found instead.");
    next = this->lex.nextToken();
    if (next.getType() != TokenType::SEMICOLON)
        throw string("\"" + TokenTypeNames[TokenType::SEMICOLON] + "\" expected at line " + next.getLine() + "but \"" + TokenTypeNames[(int)next.getType()] + "\" found instead");
}

void Parser::compileVariableDeclaration () throw (string)
{
    Token next = this->lex.nextToken();
    if (next.getType() != TokenType::VARIABLE)
        throw string("\"" + TokenTypeNames[TokenType::VARIABLE] + "\" expected at line " + next.getLine() + "but \"" + TokenTypeNames[(int)next.getType()] + "\" found instead");
    next = this->lex.nextToken();]
    if (next.getType() != TokenType::IDENTIFIER)
        throw string("\"" + TokenTypeNames[TokenType::IDENTIFIER] + "\" expected at line " + next.getLine() + "but \"" + TokenTypeNames[(int)next.getType()] + "\" found instead");
    vector<Symbol> params;
    params.push_back
    next = this->lex.nextToken();
    if (next.getType() == TokenType::COMMA)
        for (;;)
        {
            Token ult = next;
            if (ult.getType() == TokenType::SEMICOLON && next.getType() == TokenType::IDENTIFIER)
                break;
            if (!(ult.getType() == TokenType::COMMA && next.getType() == TokenType::IDENTIFIER))
                throw string("");
        }
}
