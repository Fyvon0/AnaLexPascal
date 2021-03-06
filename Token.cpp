#include <string>
#include <stdlib.h>
#include <algorithm>

#include "Token.h"

using namespace std;

vector<string> Token::symbols = {"program","var","begin","end",
                                 "if","then", "else", "while","do","repeat","until",
                                 "integer","boolean",":",":=","+","-","*","/",
                                 "%","procedure","function","=",
                                 "<>",">","<",">=","<=","not","or",
                                 "and","xor","(",")",".",
                                 ",",";","write","read","true","false"};

static bool isInteger (const string & s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        return false;

    char * p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

inline bool isAlphaNumString (const std::string &str)
{
    for (int i = 0; i < (int)str.size(); i++)
        if (!isalnum(str[i]))
            return false;
    return true;
}

Token::Token(const string& word, int lin) throw () : token(word), line(lin)
{
    unsigned int i;
    if (this->token == "&&")
        this->token = "and";
    else if (this->token == "||")
        this->token = "or";
    for (i = 0; i < this -> symbols.size(); i++)
        if (this -> token == this -> symbols[i])
            break;
    if (i >= this -> symbols.size()) // n�o � nenhum dos tipos j� definidos
    {
        if (isdigit(this->token[0])) // Primeiro caractere � inteiro
            if (isInteger(this -> token)) // Todos os outros tamb�m s�o inteiros
                this -> type = TokenType::INTEGER;
            else // Nem todos os caracteres s�o inteiros
                this -> type = TokenType::UNKNOWN;
        else // Primeiro caractere n�o � inteiro
            if (isAlphaNumString(this -> token)) // Todos os caracteres s�o alfanum�ricos
                this -> type = TokenType::IDENTIFIER;
            else // Nem todos os caracteres s�o alfanum�ricos
                this -> type = TokenType::UNKNOWN;
    }
    else // � um s�mbolo da linguagem
    {
        this -> type = (TokenType)i;
    }
}

string Token::getToken () const throw ()
{
    return string(this -> token);
}

TokenType Token::getType() const throw ()
{
    return this -> type;
}

int Token::getLine() const throw ()
{
    return this -> line;
}
