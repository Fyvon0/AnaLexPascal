#include "TabelaDeSimbolos.h"

TabelaDeSimbolos::TabelaDeSimbolos() {
    this->ultimoNivel = 0;
}

TabelaDeSimbolos::eliminaNivel(char nivel) { // Nojinho
    set<Simbolo>::iterator b, e;
    bool achouComeco = false;
    for (set<Simbolo>::iterator it = this->simbolos.begin(); it != this->simbolos.end(); it++)
        if (!achouComeco && it->getNivel() == nivel)
            b = it;
        else if (achouComeco && it->getNivel() != nivel) {
            e = it - 1;
            break;
        }

    this->simbolos.erase(b, e);
}

TabelaDeSimbolos::existe(Simbolo s) const {
    return this->simbolos.find(s) == this->simbolos.end();
}

TabelaDeSimbolos::inserirSimbolo(Simbolo s) const {
    this->simbolos.insert(s);
}

TabelaDeSimbolos::getUltimoNivel() const {
    return this->ultimoNivel;
}
