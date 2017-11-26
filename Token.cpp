#include <string>
#include <stdlib.h>
#include <algorithm>

#include "Token.h"

using namespace std;

vector<string> Token::simbolos ({"program","var","begin","end",
                                 "if","while","integer","boolean",
                                 ":",":=","+","-","*","div","/",
                                 "mod","procedure","function","=",
                                 "<>",">","<",">=","<=","not","or",
                                 "and","xor","<<",">>","(",")",".",
                                 ",",";","write","read"});

static bool ehInteiro (const string & s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        return false;

    char * p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

static inline bool ehCharAlfanumerico(char c)
{
    return !(isalpha(c) || isdigit(c) || (c == ' '));
}

bool ehStringAlfanumerica(const std::string &str)
{
    return find_if(str.begin(), str.end(), ehCharAlfanumerico) == str.end();
}

Token::Token(string word, int lin) throw ()
{
    this -> token = word;
    this -> linha = lin;
    unsigned int i;
    for (i = 0; i < this -> simbolos.size(); i++)
        if (this -> token == this -> simbolos[i])
            break;
    if (i >= this -> simbolos.size()) // n�o � nenhum dos tipos j� definidos
    {
        if (isalpha(this->token[0])) // Primeiro caractere � inteiro
            if (ehInteiro(this -> token)) // Todos os outros tamb�m s�o inteiros
                this -> tipo = TipoToken::inteiro;
            else // Nem todos os caracteres s�o inteiros
                this -> tipo = TipoToken::desconhecido;
        else // Primeiro caractere n�o � inteiro
            if (ehStringAlfanumerica(this -> token)) // Todos os caracteres s�o alfanum�ricos
                this -> tipo = TipoToken::identificador;
            else // Nem todos os caracteres s�o alfanum�ricos
                this -> tipo = TipoToken::desconhecido;
    }
    else // � um s�mbolo da linguagem
        this -> token = i;
}

string Token::getToken () const throw ()
{
    return string(this -> token);
}

TipoToken Token::getTipo () const throw ()
{
    return this -> tipo;
}

int Token::getLinha() const throw ()
{
    return this -> linha;
}
