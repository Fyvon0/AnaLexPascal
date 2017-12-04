#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Token.h"
#include "Lexer.h"

using namespace std;

bool inline isSymbol(char c)
{
    return c == ':' || c == '+' || c == '-'  || c == '*' || c == '=' || c == '>' || c == '<' || c == '(' || c == ')' || c == '.' || c == ',' || c == ';';
}

Lexer::Lexer(string fileName) throw (string)
{
    ifstream arq(fileName);
    if (arq.fail())
        throw string("Could not open the specified file.");

    string word;
    int line = 1;
    Token last(string("&"),0);

    do
    {
        char c = tolower(arq.get());

        if (isspace(c) && !word.empty())
        {
            Token newToken(word, line);
            last = newToken;
            this -> tokens.push_back(newToken);
            word.clear();
        }
        else if (last.getTipo() != TipoToken::IDENTIFICADOR && last.getTipo() != TipoToken::NUMERO && !isalnum(c) && !word.empty())
        {
            Token newToken(word, line);
            last = newToken;
            this -> tokens.push_back(newToken);
            word.clear();
            if (isSymbol(c))
            {
                if (c == ':')
                {
                    word += c;
                    c = arq.get();
                    if (c == '=')
                        word += c;
                    else
                        arq.unget();

                    Token newToken(word, line);
                    last = newToken;
                    this -> tokens.push_back(newToken);
                    word.clear();
                }
                else
                {
                    word += c;
                    Token newToken(word, line);
                    last = newToken;
                    this -> tokens.push_back(newToken);
                    word.clear();
                }
            }
        }
        else if ((last.getTipo() == TipoToken::IDENTIFICADOR || last.getTipo() == TipoToken::NUMERO) && isalnum(c) && !word.empty())
        {
            Token newToken(word, line);
            last = newToken;
            this -> tokens.push_back(newToken);
            word.clear();

            arq.unget();
        }
        else if(!isspace(c))
                word += c;

        if (c == '\n')
            line++;
    }while (arq.good());

    this -> iterador = 0;
}

Token Lexer::tokenAtual() const throw (string)
{
    if (!this -> temMaisTokens())
        throw string("Não existem mais tokens a serem buscados");
    Token t = this->tokens[this -> iterador];
    return t;
}

Token Lexer::avancaToken() throw (string)
{
    if (!this -> temMaisTokens())
        throw string("Não existem mais tokens a serem buscados");
    Token t = this->tokens[this -> iterador];
    ++(this -> iterador);
    return t;
}

Token Lexer::proximoToken() const throw (string)
{
    if (!this -> temMaisTokens())
        throw string("Não existem mais tokens a serem buscados");
    Token t = this->tokens[this -> iterador + 1];
    return t;
}

bool Lexer::temMaisTokens() const throw ()
{
    return this -> iterador < this -> tokens.size();
}
