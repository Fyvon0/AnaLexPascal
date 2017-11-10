#ifndef TOKEN
#define TOKEN

#include <string>

using namespace std;

typedef
    enum TipoToken {
        Comando,
        Operador,
        Constante,
        Identificador,
        Erro
    } TipoToken;

class Token {
private:
    TipoToken tipo;
    string token;

public:
    string getToken() const;
    TipoToken getTipo() const;
};

#endif // TOKEN
