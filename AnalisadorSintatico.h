#ifndef ANALISADORSINTATICO
#define ANALISADORSINTATICO

#include <list>
#include <string>

#include "AnalisadorLexico.h"
#include "TabelaDeSimbolos.h"

class AnalisadorSintatico
{
private:
    std::list<std::string> erros;
    AnalisadorLexico *AnaLex;
    TabelaDeSimbolos ts;
    char nivel;
public:
    AnalisadorSintatico (string) throw ();
    void compilaInicioDePrograma () throw (string);
    void compilaDeclaracaoDeVariavel () throw (string);
    void compilaDeclaracaoDeProcedimento () throw (string);
    void compilaDeclaracaoDeFuncao () throw (string);
    void compilaDeclaracaoDePP() throw (string);
    void compilaSe() throw (string);
    void compilaDeclaracaoDeWhile() throw (string);
    void compilaComando() throw (string);
    void compilaComandoComposto() throw (string);
};

#endif // ANALISADORSINTATICO