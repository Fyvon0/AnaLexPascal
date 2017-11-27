#include <string>
#include <typeinfo>

#include "Simbolo.h"

using namespace std;

//SIMBOLO

string Simbolo::getNome() const throw ()
{
    return string(this -> nome);
}

char Simbolo::getNivel() const throw ()
{
    return this -> nivel;
}

void Simbolo::setNivel(char nivel) throw (string) {
    if (nivel < 0)
        throw string ("Nível inválido.");

    this->nivel = nivel;
}

bool Simbolo::operator!=(Simbolo other) const throw ()
{
    return !this -> operator==(other);
}

bool Simbolo::operator==(Simbolo other) const throw ()
{
    if (this -> nivel != other.getNivel())
        return false;
    return this->nome != other.getNome();
}

//VARIAVEL
Variavel::Variavel(string s, TipoVariavel t, char n) throw ()
{
    string nom (s);
    this -> nome = nom;
    this -> tipo = t;
    this -> nivel = n;
}

TipoVariavel Variavel::getTipoVariavel() const throw ()
{
    return this -> tipo;
}

bool Variavel::operator== (Simbolo other) const throw ()
{
    if (typeid(*this) != typeid(other))
        return false;

    if (this -> nivel != other.getNivel())
        return false;

    return this -> nome == other.getNome();
}

//PARAMETRO
Parametro::Parametro(string s, TipoVariavel t, char n) throw ()
{
    string nom (s);
    this -> nome = nom;
    this -> tipo = t;
    this -> nivel = n;
}
TipoVariavel Parametro::getTipoVariavel() const throw ()
{
    return this -> tipo;
}

bool Parametro::operator== (Simbolo other) const throw ()
{
    if (typeid(*this) != typeid(other))
        return false;

    if (this -> nivel != other.getNivel())
        return false;

    return this -> nome == other.getNome();
}

bool Parametro::operator== (Parametro p) const throw ()
{
    if (this -> nivel != p.getNivel())
        return false;

    return this -> nome == p.getNome();
}


//PROCEDIMENTO
Procedimento::Procedimento(string s, char n, vector<Parametro> pars) throw ()
{
    string nom (s);
    this -> nome = nom;
    this -> nivel = n;
    vector<Parametro> p (pars);
    this -> params = p;
}

unsigned int Procedimento::getQuantidadeParametros() const throw ()
{
    return this -> params.size();
}

TipoVariavel Procedimento::getTipoParametro(unsigned int i) const throw (string)
{
    if (i >= this -> params.size())
        throw string("Índice maior que a quantidade de parâmetros");
    return this -> params.at(i).getTipoVariavel();
}

bool Procedimento::operator==(Simbolo other) const throw ()
{
    if (typeid(*this) != typeid(other))
        return false;
    if (this -> params != static_cast<Procedimento*>(&other) -> params)
        return false;
    return this -> nome == other.getNome();
}

//FUNCAO
Funcao::Funcao(string s, TipoVariavel t, char n, vector<Parametro> pars) throw()
{
    string nom (s);
    this->nome = nom;
    this->retorno = t;
    this->nivel = n;
    vector<Parametro> p (pars);
    this -> params = p;
}

unsigned int Funcao::getQuantidadeParametros() const throw ()
{
    return this -> params.size();
}

TipoVariavel Funcao::getTipoParametro(unsigned int i) const throw (string)
{
    if (i >= this -> params.size())
        throw string("Índice maior que a quantidade de parâmetros");
    return this -> params.at(i).getTipoVariavel();
}

TipoVariavel Funcao::getTipoDeRetorno() const throw ()
{
    return retorno;
}

bool Funcao::operator==(Simbolo other) const throw ()
{
    if (typeid(*this) != typeid(other))
        return false;
    if (this -> params != static_cast<Funcao*>(&other) -> params)
        return false;
    return this -> nome == other.getNome();
}
