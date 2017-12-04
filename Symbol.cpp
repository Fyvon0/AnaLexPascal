#include <string>
#include <typeinfo>

#include "Simbolo.h"

using namespace std;

//SIMBOLO

string Simbolo::getNome() const throw ()
{
    return string(this -> nome);
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
Variavel::Variavel(string s, TipoVariavel t) throw (string)
{
    if (t == TipoVariavel::VOID)
        throw("Variable cannot be void");
    this -> nome = string(s);
    this -> tipo = t;
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

//FUNCAO
Funcao::Funcao(string s, TipoVariavel t, vector<Parametro> pars) throw()
{
    this->nome = string(s);
    this->retorno = t;
    vector<Parametro> p (pars);
    this -> params = p;
}

unsigned int Funcao::getQuantidadeParametros() const throw ()
{
    return this -> params.size();
}

TipoVariavel Funcao::getTipoParametro(unsigned int i) const throw ()
{
    if (i >= this -> params.size())
        throw string("Index out of bounds.");
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
