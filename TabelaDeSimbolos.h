#ifndef TABELADESIMBOLOS
#define TABELADESIMBOLOS

using namespace std;

class TabelaDeSimbolos
{
private:
    //armazenar simbolos
    set<Simbolo, comparador> simbolos; // o primeiro vetor agrupa os símbolos por nível, enquanto o segundo os armazenada de fato
    char ultimoNivel;
    struct comparador { // Functor comparador
        bool operator() (Simbolo a, Simbolo b) const {
            char nA = a.getNivel(),
                 nB = b.getNivel();

            if (nA != nB)
                return nA < nB;

            return a.getToken() < b.getToken();
        }
    };

public:
    bool inserirSimbolo (Simbolo) throw (string);
    bool eliminaNivel (char) throw (string);
    bool existe (Simbolo) const throw ();
    char getUltimoNivel() const throw ();

    TabelaDeSimbolos()
};

#endif // TABELADESIMBOLOS
