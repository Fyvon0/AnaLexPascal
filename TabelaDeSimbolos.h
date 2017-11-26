#ifndef TABELADESIMBOLOS
#define TABELADESIMBOLOS

#include <set>

#include "Simbolo.h"

using namespace std;

class TabelaDeSimbolos
{
private:
    //armazenar simbolos
    struct comparador { // Functor comparador
        bool operator() (Simbolo a, Simbolo b) const {
            char nA = a.getNivel(),
                 nB = b.getNivel();

            if (nA != nB)
                return nA < nB;

            return a.getNome() < b.getNome();
        }
    };
    set<Simbolo, comparador> simbolos;
    char ultimoNivel;

public:
    void inserirSimbolo (Simbolo) throw (); // E se o símbolo já existir
    void eliminaNivel (char) throw (); // E se o nível for inválido?
    bool existe (Simbolo) const throw ();
    char getUltimoNivel() const throw ();

    TabelaDeSimbolos();
};

#endif // TABELADESIMBOLOS
