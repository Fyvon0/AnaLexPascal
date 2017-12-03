#include <string>
#include <stdlib.h>
#include <algorithm>

#include "Token.h"

using namespace std;

vector<string> Token::simbolos ({"program","var","begin","end",
                                 "if","while","integer","boolean",
                                 ":",":=","+","-","*","div",
                                 "mod","procedure","function","=",
                                 "<>",">","<",">=","<=","not","or",
                                 "and","xor","<<",">>","(",")",".",
                                 ",",";","writeln","readln","true","false"});

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
    for (int i = 0; i < str.size(); i++)
        if (!isalnum(str[i]))
            return false;
    return true;
}

Token::Token(string word, int lin) throw ()
{
    this -> token = word;
    this -> linha = lin;
    unsigned int i;
    for (i = 0; i < this -> simbolos.size(); i++)
        if (this -> token == this -> simbolos[i])
            break;
    if (i >= this -> simbolos.size()) // não é nenhum dos tipos já definidos
    {
        if (isdigit(this->token[0])) // Primeiro caractere é inteiro
            if (ehInteiro(this -> token)) // Todos os outros também são inteiros
                this -> tipo = TipoToken::inteiro;
            else // Nem todos os caracteres são inteiros
                this -> tipo = TipoToken::desconhecido;
        else // Primeiro caractere não é inteiro
            if (ehStringAlfanumerica(this -> token)) // Todos os caracteres são alfanuméricos
                this -> tipo = TipoToken::identificador;
            else // Nem todos os caracteres são alfanuméricos
                this -> tipo = TipoToken::desconhecido;
    }
    else // é um símbolo da linguagem
        this -> tipo = (TipoToken)i;
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
