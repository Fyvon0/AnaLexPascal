#ifndef TOKEN
#define TOKEN

#include <string>

using namespace std;

enum class TipoToken{
     PROGRAMA,       // Program
     VARIAVEL,       // var
     COMECO,         // Begin
     FIM,            // End
     SE,             // if
     ENQUANTO,       // while
     INTEIRO,        // integer
     BOOLEANO,       // boolean
     DOIS_PONTOS,     // :
     ATRIBUICAO,     // :=
     SOMA,           // +
     SUBTRACAO,      // -
     MULTIPLICACAO,  // *
     DIVISAO_INTEIRA, // div
     MODULO,         // mod
     PROCEDIMENTO,   // procedure
     FUNCAO,         // function
     IGUAL,          // =
     DIFERENTE,      // <>
     MAIOR_QUE,       // >
     MENOR_QUE,       // <
     MAIOR_IGUAL,     // >=
     MENOR_IGUAL,     // <=
     NAO,            // not -- operadores bin�rios e l�gicos s�o iguais
     OU,             // or
     E,              // and
     OR_EXCLUSIVO,         // xor
     BITS_PARA_ESQUERDA,// << ou shl
     BITS_PARA_DIREITA, // >> ou shr
     ABRE_PARENTESES, // (
     FECHA_PARENTESES,// )
     PONTO,          // . -- identifica o fim do programa
     VIRGULA,        // , -- divide declara��o de vari�veis
     PONTO_E_VIRGULA,  // ;
     ESCRITA,        // write
     LEITURA,        // read
     VERDADEIRO,     // true
     FALSO,          // false
     IDENTIFICADOR,  // nome da var ou fun��o que n�o as duas acima
     NUMERO,         // n�mero constante no meio do c�digo
     DESCONHECIDO    // s�mbolo que n�o consta acima
 };

class Token {
private:
    TipoToken tipo;
    string token;
    static vector<string> simbolos;
    int linha;

public:
    Token(string, int) throw ();
    string getToken() const throw ();
    TipoToken getTipo() const throw ();
    int getLinha() const throw ();
};

#endif // TOKEN
