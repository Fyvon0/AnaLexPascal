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
