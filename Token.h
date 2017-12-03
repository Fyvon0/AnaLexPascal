#ifndef TOKEN
#define TOKEN

#include <string>

using namespace std;

enum class TipoToken{
     programa,       // Program
     variavel,       // var
     comeco,         // Begin
     fim,            // End
     se,             // if
     enquanto,       // while
     inteiro,        // integer
     booleano,       // boolean
     doisPontos,     // :
     atribuicao,     // :=
     soma,           // +
     subtracao,      // -
     multiplicacao,  // *
     divisaoInteira, // div
     modulo,         // mod
     procedimento,   // procedure
     funcao,         // function
     igual,          // =
     diferente,      // <>
     maiorQue,       // >
     menorQue,       // <
     maiorIgual,     // >=
     menorIgual,     // <=
     nao,            // not -- operadores binários e lógicos são iguais
     ou,             // or
     e,              // and
     exclOr,         // xor
     bitsPraEsquerda,// << ou shl
     bitsPraDireita, // >> ou shr
     abreParenteses, // (
     fechaParenteses,// )
     ponto,          // . -- identifica o fim do programa
     virgula,        // , -- divide declaração de variáveis
     pontoEVirgula,  // ;
     escrita,        // write
     leitura,        // read
     verdadeiro,     // true
     falso,          // false
     identificador,  // nome da var ou função que não as duas acima
     numero,         // número constante no meio do código
     desconhecido    // símbolo que não consta acima
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
