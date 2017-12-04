#ifndef PARSER
#define PARSER

#include <list>
#include <string>

#include "Lexer.h"
#include "SymbolTable.h"

class Parser
{
private:
    Lexer lex;
    SymbolTable st;

    void compileProgramStart () throw (string);
public:
    Parser(string) throw ();
};

>>>>>>> 2fd5d82b58db4a69486c096331b871f04fd5625b:Parser.h
/*
class AnalisadorSintatico
{
private:
    std::list<std::string> erros;
    Lexer *lexer;
    TabelaDeSimbolos ts;

    bool isNumberOrIdentifier(Token t)const throw();
    void compilaInicioDePrograma () throw (string);
    void compilaDeclaracaoDeVariavel () throw (string);
    void compilaDeclaracaoDeProcedimento () throw (string);
    void compilaDeclaracaoDeFuncao () throw (string);
    void compilaDeclaracaoDePP() throw (string);
    void compilaSe() throw (string);
    void compilaDeclaracaoDeWhile() throw (string);
    void compilaComando() throw (string);
    void compilaComandoComposto() throw (string);
    void compilaExpressaoRelacional() throw (string);
    void compilaEnquanto() throw (string);
    void compilaExpressaoAritmetica() throw (string);
    void compilaFator() throw (string);
    void compilaChamadaDeProc() throw (string);
    void compilaAtribuicao() throw (string);
    VariableType compilaExpressao() throw (string);
    VariableType compilaChamadaDeFunc() throw (string);
public:
    AnalisadorSintatico (string) throw ();
    void compilar() throw (string);
<<<<<<< HEAD:AnalisadorSintatico.h
}; */

#endif // ANALISADORSINTATICO
=======
};
*/
#endif // PARSER
>>>>>>> 2fd5d82b58db4a69486c096331b871f04fd5625b:Parser.h
