#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Token.h"
#include "AnalisadorLexico.h"

using namespace std;

bool inline isSimbolo(char c)
{
    return c == ':' || c == '+' || c == '-'  || c == '*' || c == '=' || c == '>' || c == '<' || c == '(' || c == ')' || c == '.' || c == ',' || c == ';';
}

AnalisadorLexico::AnalisadorLexico(string nomeArq) throw (string)
{
    ifstream arq(nomeArq);
    if (arq.fail())
        throw string("Nao foi possivel abrir o arquivo indicado");

    string word;
    int linha = 1;
    Token ult(string("&"),0);

    do
    {
        char c = tolower(arq.get());

        if (isspace(c) && !word.empty())
        {
            Token newToken(word, linha);
            ult = newToken;
            this -> tokens.push_back(newToken);
            word.clear();
        }
        else if (ult.getTipo() != TipoToken::identificador && ult.getTipo() != TipoToken::numero && !isalnum(c) && !word.empty())
        {
            Token newToken(word, linha);
            ult = newToken;
            this -> tokens.push_back(newToken);
            word.clear();
            if (isSimbolo(c))
            {
                if (c == ':')
                {
                    word += c;
                    c = arq.get();
                    if (c == '=')
                        word += c;
                    else
                        arq.unget();

                    Token newToken(word, linha);
                    ult = newToken;
                    this -> tokens.push_back(newToken);
                    word.clear();
                }
                else
                {
                    word += c;
                    Token newToken(word, linha);
                    ult = newToken;
                    this -> tokens.push_back(newToken);
                    word.clear();
                }
            }
        }
        else if ((ult.getTipo() == TipoToken::identificador || ult.getTipo() == TipoToken::numero) && isalnum(c) && !word.empty())
        {
            Token newToken(word, linha);
            ult = newToken;
            this -> tokens.push_back(newToken);
            word.clear();

            arq.unget();
        }
        else if(!isspace(c))
                word += c;

        if (c == '\n')
            linha++;
    }while (arq.good());

    this -> iterador = 0;
}

Token AnalisadorLexico::tokenAtual() const throw (string)
{
    if (!this -> temMaisTokens())
        throw string("Não existem mais tokens a serem buscados");
    Token t = this->tokens[this -> iterador];
    return t;
}

Token AnalisadorLexico::avancaToken() throw (string)
{
    if (!this -> temMaisTokens())
        throw string("Não existem mais tokens a serem buscados");
    Token t = this->tokens[this -> iterador];
    ++(this -> iterador);
    return t;
}

Token AnalisadorLexico::proximoToken() const throw (string)
{
    if (!this -> temMaisTokens())
        throw string("Não existem mais tokens a serem buscados");
    Token t = this->tokens[this -> iterador + 1];
    return t;
}

bool AnalisadorLexico::temMaisTokens() const throw ()
{
    return this -> iterador < this -> tokens.size();
}
