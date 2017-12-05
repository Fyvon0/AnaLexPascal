#include <string>
#include <stdlib.h>
#include <algorithm>

#include "Token.h"

using namespace std;

vector<string> Token::symbols = {"program","var","begin","end",
                                 "if","while","integer","boolean",
                                 ":",":=","+","-","*","div",
                                 "mod","procedure","function","=",
                                 "<>",">","<",">=","<=","not","or",
                                 "and","xor","(",")",".",
                                 ",",";","writeln","readln","true","false"};

static bool isInteger (const string & s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        return false;

    char * p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

bool isAlphaNumString (const std::string &str)
{
    for (int i = 0; i < str.size(); i++)
        if (!isalnum(str[i]))
            return false;
    return true;
}

Token::Token(string word, int lin)
 throw ()
{
    this -> token = word;
    this -> line = lin;
    unsigned int i;
    for (i = 0; i < this -> symbols.size(); i++)
        if (this -> token == this -> symbols[i])
            break;
    if (i >= this -> symbols.size()) // não é nenhum dos tipos já definidos
    {
        if (isdigit(this->token[0])) // Primeiro caractere é inteiro
            if (isInteger(this -> token)) // Todos os outros também são inteiros
                this -> type = TokenType::INTEGER;
            else // Nem todos os caracteres são inteiros
                this -> type = TokenType::UNKNOWN;
        else // Primeiro caractere não é inteiro
            if (isAlphaNumString(this -> token)) // Todos os caracteres são alfanuméricos
                this -> type = TokenType::IDENTIFIER;
            else // Nem todos os caracteres são alfanuméricos
                this -> type = TokenType::UNKNOWN;
    }
    else // é um símbolo da linguagem
        this -> type = (TokenType)i;
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
