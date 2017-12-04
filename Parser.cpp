#include "Parser.h"


string TokenTypeNames[] = {"PROGRAM","VAR","BEGIN","END","IF","WHILE","INTEGER","BOOLEAN","COLON","ATTRIBUTION","SUM",
                           "SUBTRACTION","MULTIPLICATION","DIVISION","MODULE","PROCEDURE","FUNCTION","=","!=",">","<",
                           ">=","<=","NOT","OR","AND","XOR","(",")",".",",",";","WRITE","READ","TRUE","FALSE",
                           "IDENTIFIER","CONSTANT","UNKNOWN"};

Parser::Parser(string path) throw () : lex(path) {}

void throwExpected(TokenType expected, int line, TokenType found) throw (string) {
    throw string ("\"" + TokenTypeNames[(int)expected] +
                  "\" expected at line " +
                  std::to_string(line) +
                  " but \"" +
                  TokenTypeNames[(int)found] +
                  "\" found instead.");
}

void Parser::compileProgramStart () throw (string)
{
    Token next = this->lex.nextToken();
    if (next.getType() != TokenType::PROGRAM)
        throwExpected(TokenType::PROGRAM, next.getLine(), next.getType());
    next = this->lex.nextToken();
    if (next.getType() != TokenType::IDENTIFIER)
        throwExpected(TokenType::IDENTIFIER, next.getLine(), next.getType());
    next = this->lex.nextToken();
    if (next.getType() != TokenType::SEMICOLON)
        throwExpected(TokenType::SEMICOLON, next.getLine(), next.getType());
}

void Parser::compileVariableDeclaration () throw (string)
{
    Token next = this->lex.nextToken();
    if (next.getType() != TokenType::VARIABLE)
        throwExpected(TokenType::VARIABLE, next.getLine(), next.getType());
    next = this->lex.nextToken();
    if (next.getType() != TokenType::IDENTIFIER)
        throwExpected(TokenType::IDENTIFIER, next.getLine(), next.getType());
    vector<string> params;
    params.push_back(next.getToken());
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
