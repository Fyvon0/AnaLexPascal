#include <sstream>
#include <forward_list>

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
    vector<Symbol> params;
    while (true)
    {
        bool sameType = true;
        forward_list<Token> pars;
        while (sameType)
        {
            pars.push_front(next);
            next = this->lex.nextToken();
            if (next.getType() == TokenType::COLON)
                sameType = false;
            else if (next.getType() == TokenType::COMMA)
                next = this->lex.nextToken();
            else
                this->throwExpected(TokenType::COMMA, next.getLine(), next.getType());
        }
        next = this->lex.nextToken();
        if (next.getType() ==TokenType::INTEGER)
        {
            for (auto it = pars.cbegin(); it != pars.cend(); it++)
            {
                Symbol p ((*it).getToken(), VariableType::INTEGER, nullptr);
                params.push_back(p);
                this->st.insertSymbol(p);

            }
            pars.clear();
        }
        else if  (next.getType() == TokenType::BOOLEAN)
        {
            for (auto it = pars.cbegin(); it != pars.cend(); it++)
            {
                Symbol p ((*it).getToken(), VariableType::BOOLEAN ,nullptr);
                params.push_back(p);
                this->st.insertSymbol(p);
            }
            pars.clear();
        }
        else
            this->throwExpected(TokenType::VARIABLE, next.getLine(), next.getType());
        next = this->lex.nextToken();
        if (next.getType() == TokenType::SEMICOLON)
        {
            if (this->lex.peekToken().getType() != TokenType::IDENTIFIER)
                break;
            next = this->lex.nextToken();
        }
        else
            this->throwExpected(TokenType::SEMICOLON, next.getLine(), next.getType());
    }
}
    /*
    params.push_back(next.getToken());
    next = this->lex.nextToken();
    if (next.getType() == TokenType::COMMA)
        for (;;)
        {
            Token ult = next;
            if (ult.getType() == TokenType::SEMICOLON && next.getType() == TokenType::IDENTIFIER)
                break;
            if ((ult.getType() == TokenType::COMMA && next.getType() == TokenType::IDENTIFIER) || (next.getType() == TokenType::COMMA && ult.getType() == TokenType::IDENTIFIER))
                continue;
            if (ult.getType() == TokenType::IDENTIFIER)
                this->throwExpected(TokenType::COMMA, next.getLine(), next.getType());
            if (ult.getType() == TokenType::COMMA)
                this->throwExpected(TokenType::IDENTIFIER, next.getLine(), next.getType());
            throw string ("ESSO NON ECZISTE!!!");
        }
    */

