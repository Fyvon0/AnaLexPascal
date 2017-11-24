#ifndef TABELADESIMBOLOS
#define TABELADESIMBOLOS

class TabelaDeSimbolos
{
private:
    //armazenar simbolos
    vector<vector<Simbolo>> simbolos; // o primeiro vetor agrupa os s�mbolos por n�vel, enquanto o segundo os armazenada de fato
public:
    bool inserirSimbolo (Simbolo, char) throw (string);
    bool eliminaNivel (unsigned int) throw (string);
    bool existe (Simbolo) const throw ();
};

#endif // TABELADESIMBOLOS
