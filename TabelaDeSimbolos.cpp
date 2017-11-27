#include <typeinfo>

#include "TabelaDeSimbolos.h"

TabelaDeSimbolos::TabelaDeSimbolos() {
    this->ultimoNivel = 0;
}

void TabelaDeSimbolos::voltarNivel() throw (string) { // Nojinho
    if (this->ultimoNivel <= 0)
        throw string ("N�o pode voltar mais um n�vel");

    set<Simbolo>::iterator b, e;
    bool achouComeco = false;
    for (set<Simbolo>::iterator it = this->simbolos.cbegin(); it != this->simbolos.cend(); it++)
        if (!achouComeco && it->getNivel() == this->ultimoNivel)
            b = it;
        else if (achouComeco && it->getNivel() != this->ultimoNivel) {
            e = it - 1; // CORRIGIR ESSA PORRINHA AQUI
            break;
        }

    this->simbolos.erase(b, e);
    this->ultimoNivel--;
}

void TabelaDeSimbolos::avancarNivel() throw() {
    this->ultimoNivel++;
}

bool TabelaDeSimbolos::existe(Simbolo s) const throw () {
    return this->simbolos.find(s) == this->simbolos.end();
}

void TabelaDeSimbolos::inserirSimbolo(Simbolo s) throw () {
    this->inserirSimbolo(s, this->ultimoNivel);
}

void TabelaDeSimbolos::inserirSimbolo(Simbolo s, char nivel) throw (string) {
    if (existe(s))
        throw string ("N�o pode inserir s�mbolo repetido.");
    s.setNivel(nivel);
    this->simbolos.insert(s);
}

char TabelaDeSimbolos::getUltimoNivel() const throw () {
    return this->ultimoNivel;
}

Simbolo TabelaDeSimbolos::getSimbolo(string nome) const throw (string) {
    for (auto it = simbolos.cbegin(); it != simbolos.cend(); it++)
        if (it->getNivel() != this->ultimoNivel)
            continue;
        else if (it->getNome() == nome)
            return *it;

    throw string ("Tipo n�o declarado");
}

TipoSimbolo TabelaDeSimbolos::getTipo(string nome) const throw (){
    for (auto it = simbolos.cbegin(); it != simbolos.cend(); it++)
        if (it->getNivel() != this->ultimoNivel) // S� para s�mbolos do n�vel atual
            continue;
        else if (it->getNome() == nome)
        {
            switch (typeid(*it))
            {
            case typeid(Variavel):
                return TipoSimbolo::Variavel;
            case typeid(Parametro):
                return TipoSimbolo::Parametro;
            case typeid(Procedimento):
                return TipoSimbolo::Procedimento;
            case typeid(Funcao):
                return TipoSimbolo::Funcao;
            }
        }

    return TipoSimbolo::Nenhum;
}
