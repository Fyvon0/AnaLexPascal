#include <typeinfo>

#include "TabelaDeSimbolos.h"

TabelaDeSimbolos::TabelaDeSimbolos() {
    this->ultimoNivel = 0;
}

void TabelaDeSimbolos::voltarNivel() throw (string) {
    if (this->ultimoNivel <= 0)
        throw string ("Não pode voltar mais um nível");

    set<Simbolo>::iterator b, e;
    bool achouComeco = false;
    for (set<Simbolo>::iterator it = this->simbolos.cbegin(); it != this->simbolos.cend(); it++)
        if (!achouComeco && it->getNivel() == this->ultimoNivel)
            b = it;
        else if (achouComeco && it->getNivel() != this->ultimoNivel) {
            e = it;
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

void TabelaDeSimbolos::inserirSimbolo(Simbolo s) throw (string) {
    if (existe(s))
        throw string ("Não pode inserir símbolo repetido.");
    this->inserirSimbolo(s, this->ultimoNivel);
}

void TabelaDeSimbolos::inserirSimbolo(Simbolo s, char nivel) throw (string) {
    if (existe(s))
        throw string ("Não pode inserir símbolo repetido.");
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

    throw string ("Tipo não declarado");
}

TipoSimbolo TabelaDeSimbolos::getTipo(string nome) throw (){
    for (auto it = simbolos.begin(); it != simbolos.end(); it++)
        if (it->getNivel() != this->ultimoNivel) // Só para símbolos do nível atual
            continue;
        else if (it->getNome() == nome)
        {
            if (typeid(*it) == typeid(Variavel))
                return TipoSimbolo::Variavel;
            if (typeid(*it) == typeid(Parametro))
                return TipoSimbolo::Parametro;
            if (typeid(*it) == typeid(Procedimento))
                return TipoSimbolo::Procedimento;
            if (typeid(*it) == typeid(Funcao))
                return TipoSimbolo::Funcao;
        }
    return TipoSimbolo::Nenhum;
}
