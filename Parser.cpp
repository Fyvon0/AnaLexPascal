#include <sstream>

#include "Parser.h"


string TokenTypeNames[] = {"PROGRAM","VAR","BEGIN","END","IF","WHILE","INTEGER","BOOLEAN","COLON","ATTRIBUTION","SUM",
                           "SUBTRACTION","MULTIPLICATION","DIVISION","MODULE","PROCEDURE","FUNCTION","=","!=",">","<",
                           ">=","<=","NOT","OR","AND","XOR","(",")",".",",",";","WRITE","READ","TRUE","FALSE",
                           "IDENTIFIER","CONSTANT","UNKNOWN"};

Parser::Parser(string path) throw () : lex(path) {}


template <typename T>
std::string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}

void Parser::throwExpected(TokenType expected, int line, TokenType found) throw (string) {
    throw string ("\"" + TokenTypeNames[(int)expected] +
                  "\" expected at line " +
                  to_string(line) +
                  " but \"" +
                  TokenTypeNames[(int)found] +
                  "\" found instead.");
}

void Parser::compileProgramStart () throw (string)
{
    Token next = this->lex.nextToken();
    if (next.getType() != TokenType::PROGRAM)
        this->throwExpected(TokenType::PROGRAM, next.getLine(), next.getType());
    next = this->lex.nextToken();
    if (next.getType() != TokenType::IDENTIFIER)
        this->throwExpected(TokenType::IDENTIFIER, next.getLine(), next.getType());
    next = this->lex.nextToken();
    if (next.getType() != TokenType::SEMICOLON)
        this->throwExpected(TokenType::SEMICOLON, next.getLine(), next.getType());
}

void Parser::compileVariableDeclaration () throw (string)
{
    Token next = this->lex.nextToken();
    if (next.getType() != TokenType::VARIABLE)
        this->throwExpected(TokenType::VARIABLE, next.getLine(), next.getType());
    next = this->lex.nextToken();
    if (next.getType() != TokenType::IDENTIFIER)
        this->throwExpected(TokenType::IDENTIFIER, next.getLine(), next.getType());
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
