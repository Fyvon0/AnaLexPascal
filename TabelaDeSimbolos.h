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
    void inserirSimbolo (Simbolo) throw (string); // E se o símbolo já existir
    void inserirSimbolo (Simbolo, char) throw (string);
    void voltarNivel() throw (string); // E se o nível for inválido?
    void avancarNivel() throw ();
    bool existe (Simbolo) const throw ();
    char getUltimoNivel() const throw ();
    Simbolo getSimbolo(string) const throw (string);
    TipoSimbolo getTipo (string) const throw ();

    TabelaDeSimbolos();
};

#endif // TABELADESIMBOLOS
