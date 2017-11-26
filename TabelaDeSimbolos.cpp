#include <typeinfo>

#include "TabelaDeSimbolos.h"

TabelaDeSimbolos::TabelaDeSimbolos() {
    this->ultimoNivel = 0;
}

void TabelaDeSimbolos::eliminaNivel(char nivel) throw () { // Nojinho
    set<Simbolo>::iterator b, e;
    bool achouComeco = false;
    for (set<Simbolo>::iterator it = this->simbolos.begin(); it != this->simbolos.end(); it++)
        if (!achouComeco && it->getNivel() == nivel)
            b = it;
        else if (achouComeco && it->getNivel() != nivel) {
            e = it - 1; // CORRIGIR ESSA PORRINHA AQUI
            break;
        }

    this->simbolos.erase(b, e);
}

bool TabelaDeSimbolos::existe(Simbolo s) const throw () {
    return this->simbolos.find(s) == this->simbolos.end();
}

void TabelaDeSimbolos::inserirSimbolo(Simbolo s) throw () {
    this->simbolos.insert(s);
}

char TabelaDeSimbolos::getUltimoNivel() const throw (){
    return this->ultimoNivel;
}

TipoSimbolo TabelaDeSimbolos::getTipo(string nome) const throw (){
    for (auto it = set.cbegin(); it != set.cend(); it++)
        if ((*it).getNome() == nome)
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
