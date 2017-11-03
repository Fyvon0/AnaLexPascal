#ifndef ANALEX
#define ANALEX

#include <string>
#include <fstream>

using namespace std;

enum TipoPedaco{
    programa,       // Program
    variavel,       // var
    comeco,         // Begin
    fim,            // End
    se,             // if
    enquanto,       // while
    inteiro,        // integer
    booleano,       // boolean
    tipoVariavel,   // :
    atribuicao,     // :=
    soma,           // +
    subtracao,      // -
    multiplicacao,  // *
    divisaoInteira, // div
    divisaoReal,    // /
    modulo,         // mod
    procedimento,   // procedure
    funcao,         // function
    igual,          // =
    diferente,      // <>
    maiorQue,       // >
    menorQue,       // <
    maiorIgual,     // >=
    menorIgual,     // <=
    //em,             // in
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
    identificador,  // nome da var ou função que não as duas acima
    numero,         // número constante no meio do código
    desconhecido    // símbolo que não consta acima
};

class AnalisadorLexico
{
private:
    static string simbolos[];
    ifstream myfile;

public:
    AnalisadorLexico (string);
    ~AnalisadorLexico ();
    TipoPedaco proximoPedaco ();
    bool temMaisPedacos ();
    string getNome (); // lança exceção se o último pedaço lido não for iodentificador ou desconhecido
    int getValor ();  // lança exceção se o último pedaco lido não for número
};

#endif // ANALEX
