#include <forward_list>
#include <string>

#include "AnalisadorSintatico.h"

AnalisadorSintatico::AnalisadorSintatico(string nomeArq) throw ()
{
    this -> AnaLex = new AnalisadorLexico(nomeArq);
    nivel = 0;
}

void AnalisadorSintatico::compilaInicioDePrograma() throw (string)
{
    Token prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::programa)
        //erros.push_back("\"Program\" expected at line " + prox.getLinha());
        throw string ("\"Program\" expected at line " + prox.getLinha());
    Token ult = prox;
    prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::identificador)
        //erros.push_back("Identifier expected at line " + ult.getLinha());
        throw string ("Identifier expected at line " + ult.getLinha());
    prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::pontoEVirgula)
        //erros.push_back("\";\" expected at line" + ult.getLinha());
        throw string ("\";\" expected at line " + ult.getLinha());
}

void AnalisadorSintatico::compilaDeclaracaoDePP() throw (string)
{
    this -> compilaComandoComposto();
    Token prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::ponto)
        //erros.push_back("\".\" expected at line " + prox.getLinha());
        throw string ("\".\" expected at line " + prox.getLinha());
}

/*void AnalisadorSintatico::compilaDeclaracaoDeProcedimento() throw (string)
{
    nivel++;
    Token prox = this->AnaLex->consomeToken();
    if (prox.getTipo() != TipoToken::procedimento)
        throw string ("\"procedure\" expected at line " + prox.getLinha());
    Token ult = prox;
    prox = this->AnaLex->consomeToken();
    if (prox.getTipo() != TipoToken::identificador)
        throw string ("Identifier expected at line " + ult.getLinha());
    string nome = prox.getToken();
    ult = prox;
    prox = this->AnaLex->consomeToken();
    if (prox.getTipo() != TipoToken::abreParenteses)
        throw string ("\"(\" expected at line " + ult.getLinha());
    ult = prox;
    prox = this->AnaLex->consomeToken();
    vector<Parametro> params;
    if (prox.getTipo() == TipoToken::identificador)
    {
        while (prox.getTipo() != TipoToken::fechaParenteses)
        {
            bool mesmoTipo = true;
            forward_list<Token> pars;
            while (mesmoTipo)
            {
                pars.push_front(prox);
                ult = prox;
                prox = this->AnaLex->consomeToken();
                if (prox.getTipo() == TipoToken::doisPontos)
                    mesmoTipo = false;
                else if (prox.getTipo() == TipoToken::virgula)
                {
                    ult = prox;
                    prox = this->AnaLex->consomeToken();
                }
                else
                    throw ("\":\" or \",\" expected at line " + ult.getLinha());
            }
            ult = prox;
            prox = this->AnaLex->consomeToken();
            if (prox.getTipo() == TipoToken::inteiro)
            {
                for (auto it = pars.cbegin(); it != pars.cend(); it++)
                {
                    Parametro p ((*it).getToken(), TipoVariavel::integer ,nivel);
                    params.push_back(p);
                    this->ts.inserirSimbolo(p);

                }
                pars.clear();
            }
            else if  (prox.getTipo() == TipoToken::booleano)
            {
                for (auto it = pars.cbegin(); it != pars.cend(); it++)
                {
                    Parametro p ((*it).getToken(), TipoVariavel::boolean ,nivel);
                    params.push_back(p);
                    this->ts.inserirSimbolo(p);
                }
                pars.clear();
            }
            else
                throw string ("Variable type expected at line " + ult.getLinha());
            ult = prox;
            prox = this->AnaLex->consomeToken();
            if (prox.getTipo() == TipoToken::pontoEVirgula)
            {
                ult = prox;
                prox = this->AnaLex->consomeToken();
            }
            else if (prox.getTipo() != TipoToken::fechaParenteses)
                throw ("\")\" expected after variable declaration at line " + ult.getLinha());
        }
    }
    if (prox.getTipo() != TipoToken::fechaParenteses)
        throw string ("\")\" expected at line " + ult.getLinha());

    ult = prox;
    prox = this->AnaLex->consomeToken();
    if (prox.getTipo() != TipoToken::pontoEVirgula)
        throw string ("\";\" expected at line after procedure declaration" + ult.getLinha());
    ult = prox;
    prox = this->AnaLex->consomeToken();
    if (prox.getTipo() == TipoToken::variavel)
    {
        while (prox.getTipo() != TipoToken::comeco)
        {
            bool mesmoTipo = true;
            forward_list<Token> vars;
            while (mesmoTipo)
            {
                vars.push_front(prox);
                ult = prox;
                prox = this->AnaLex->consomeToken();
                if (prox.getTipo() == TipoToken::doisPontos)
                    mesmoTipo = false;
                else if (prox.getTipo() == TipoToken::virgula)
                {
                    ult = prox;
                    prox = this->AnaLex->consomeToken();
                }
                else
                    throw ("\":\" or \",\" expected at line " + ult.getLinha());
            }
            ult = prox;
            prox = this->AnaLex->consomeToken();
            if (prox.getTipo() == TipoToken::inteiro)
            {
                for (auto it = vars.cbegin(); it != vars.cend(); it++)
                {
                    Variavel v ((*it).getToken(), TipoVariavel::integer ,nivel);
                    this->ts.inserirSimbolo(v);

                }
                vars.clear();
            }
            else if  (prox.getTipo() == TipoToken::booleano)
            {
                for (auto it = vars.cbegin(); it != vars.cend(); it++)
                {
                    Variavel v ((*it).getToken(), TipoVariavel::boolean ,nivel);
                    this->ts.inserirSimbolo(v);
                }
                vars.clear();
            }
            else
                throw string ("Variable type expected at line " + ult.getLinha());
            ult = prox;
            prox = this->AnaLex->consomeToken();
            if (prox.getTipo() == TipoToken::pontoEVirgula)
            {
                ult = prox;
                prox = this->AnaLex->consomeToken();
            }
            else if (prox.getTipo() != TipoToken::comeco)
                throw ("\"begin\" expected after variable declaration at line " + ult.getLinha());
        }
    }

    if (prox.getTipo() != TipoToken::comeco)
        throw string ("\"begin\" expected at line " + prox.getLinha());


    nivel--;
    ts.inserirSimbolo(Procedimento(nome,nivel,params));
}*/

void AnalisadorSintatico::compilaSe ()
{
	Token prox = this->AnaLex->avancaToken();
	if (prox.getTipo() != TipoToken::se)
		throw string ("\"if\" expected at line " + prox.getLinha());
	tipo = AS.compilarExpressao();
	if (tipo != booleano)
		erro
	prox = this->AnaLex->avancaToken();
	if (prox.getTipo() == TipoToken::comeco)
		this -> compilaComandoComposto();
	else
		this -> compilaComando();
	prox = this->AnaLex->avancaToken();
	if (prox.getTipo() != TipoToken::pontoEVirgula)
		throw ("\";\" expected at line " + prox.getLinha());
}

void AnalisadorSintatico::compilaComando() throw (string)
{
    Token prox = this->AnaLex->tokenAtual();
	if (prox.getTipo() == TipoToken::identificador) // MUDAR ISSO
	{
		//achar id na tabela de simbolos
		if (for id de var)
			compilaAtribuicao();
		else
			if (for id de proc)
				compilaChamadaDeProc();
			else
				erro
	}
	else
	{
		if (prox.getTipo() == TipoToken::se)
			this -> compilaSe();
		else if (prox.getTipo() == TipoToken::enquanto)
				this -> compilaEnquanto();
		else
            throw string ("How did you even manage to come up with this?")
	}
}

void AnalisadorSintatico::compilaComandoComposto() throw (string)
{
	Token prox = this->AnaLex->avancaToken();
	if (prox.getTipo() != TipoToken::comeco)
		throw string ("\"begin\" expected at line " + prox.getLinha());
	while (true) //MUDAR ISSO
	{
		this->compilaComando();
	}
	prox = AnaLex->avancaToken();
	if (prox.getTipo() != TipoToken::fim)
		throw string ("\"end\" expected at line " + prox.getLinha());
}
