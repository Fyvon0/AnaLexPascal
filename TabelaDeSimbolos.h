#ifndef TABELADESIMBOLOS
#define TABELADESIMBOLOS

using namespace std;

class TabelaDeSimbolos
{
private:
    //armazenar simbolos
    set<Simbolo> simbolos; // o primeiro vetor agrupa os símbolos por nível, enquanto o segundo os armazenada de fato
    char ultimoNivel;
public:
    bool inserirSimbolo (Simbolo, char) throw (string);
    bool eliminaNivel (char) throw (string);
    bool existe (Simbolo, char) const throw ();
    char getUltimoNivel() const throw ();

    TabelaDeSimbolos()
};

#endif // TABELADESIMBOLOS
