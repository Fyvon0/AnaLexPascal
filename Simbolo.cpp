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

bool Simbolo::operator!=(Simbolo other) const throw ()
{
    return !this -> operator==(other);
}

//VARIAVEL
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
TipoVariavel Parametro::getTipoVariavel() const throw ()
{
    return this -> tipo;
}

bool Parametro::operator== (Simbolo other) const throw ()
{
    if (typeid(*this) != typeid(other))
        return false;
    return this -> nome == other.getNome();
}

//PROCEDIMENTO
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
    return retorno.getTipoVariavel();
}

bool Funcao::operator==(Simbolo other) const throw ()
{
    if (typeid(*this) != typeid(other))
        return false;
    //if (this -> params != (Procedimento)other.params)
      //  return false;
    return this -> nome == other.getNome();
}
