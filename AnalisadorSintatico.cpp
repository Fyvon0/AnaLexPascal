#include "AnalisadorSintatico.h"

AnalisadorSintatico::AnalisadorSintatico(string nomeArq) throw ()
{
    this -> AnaLex = new AnalisadorLexico(nomeArq);
}

void AnalisadorSintatico::compilaDeclaracaoDePP() throw ()
{
    compilaComandoComposto();
    Token prox = this->AnaLex->consomeToken();
    if (prox.getTipo() != TipoToken::ponto)
        erros.push_back("\".\" expected at line " + prox.getLinha());
}
