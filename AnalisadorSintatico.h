#ifndef ANALISADORSINTATICO
#define ANALISADORSINTATICO

#include <list>
#include <string>

#include "AnalisadorLexico.h"

class AnalisadorSintatico
{
private:
    std::list<std::string> erros;
    AnalisadorLexico *AnaLex;
public:
    AnalisadorSintatico (string) throw ();
    void compilaInicioDePrograma () throw ();
    void compilaDeclaracaoDeVariavel () throw ();
    void compilaDeclaracaoDeProcedimento () throw ();
    void compilaDeclaracaoDeFuncao () throw ();
    void compilaDeclaracaoDePP() throw ();
    void compilaDeclaracaoDeIf() throw ();
    void compilaDeclaracaoDeWhile() throw ();
    void compilaComandoComposto() throw ();
};

#endif // ANALISADORSINTATICO
