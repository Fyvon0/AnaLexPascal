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
    nao,            // not -- operadores bin�rios e l�gicos s�o iguais
    ou,             // or
    e,              // and
    exclOr,         // xor
    bitsPraEsquerda,// << ou shl
    bitsPraDireita, // >> ou shr
    abreParenteses, // (
    fechaParenteses,// )
    ponto,          // . -- identifica o fim do programa
    virgula,        // , -- divide declara��o de vari�veis
    pontoEVirgula,  // ;
    escrita,        // write
    leitura,        // read
    identificador,  // nome da var ou fun��o que n�o as duas acima
    numero,         // n�mero constante no meio do c�digo
    desconhecido    // s�mbolo que n�o consta acima
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
    string getNome (); // lan�a exce��o se o �ltimo peda�o lido n�o for iodentificador ou desconhecido
    int getValor ();  // lan�a exce��o se o �ltimo pedaco lido n�o for n�mero
};

#endif // ANALEX
