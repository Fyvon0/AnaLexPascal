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
    prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::identificador)
        //erros.push_back("Identifier expected at line " + ult.getLinha());
        throw string ("Identifier expected at line " + prox.getLinha());
    prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::pontoEVirgula)
        //erros.push_back("\";\" expected at line" + ult.getLinha());
        throw string ("\";\" expected at line " + prox.getLinha());
}

void AnalisadorSintatico::compilaDeclaracaoDeVariavel() throw (string)
{
    Token prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::variavel)
        throw("\"var\" expected at line " + prox.getLinha());
    prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::identificador)
        throw string("Identifier expected at line " + prox.getLinha());
    vector<Parametro> params;
    while (true)
    {
        bool mesmoTipo = true;
        forward_list<Token> pars;
        while (mesmoTipo)
        {
            pars.push_front(prox);
            prox = this->AnaLex->avancaToken();
            if (prox.getTipo() == TipoToken::doisPontos)
                mesmoTipo = false;
            else if (prox.getTipo() == TipoToken::virgula)
                prox = this->AnaLex->avancaToken();
            else
                throw ("\":\" or \",\" expected at line " + prox.getLinha());
        }
        prox = this->AnaLex->avancaToken();
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
            throw string ("Variable type expected at line " + prox.getLinha());
        prox = this->AnaLex->avancaToken();
        if (prox.getTipo() == TipoToken::pontoEVirgula)
        {
            if (this->AnaLex->proximoToken().getTipo() != TipoToken::identificador)
                break;
            prox = this->AnaLex->avancaToken();
        }
        else
            throw ("\";\" expected after variable declaration at line " + prox.getLinha());
    }
}

void AnalisadorSintatico::compilaDeclaracaoDeProcedimento() throw (string)
{
    this->nivel++;
	Token prox = this->AnaLex->avancaToken();
	if (prox.getTipo() != TipoToken::procedimento)
		throw string("\"procedure\" expected at line " + prox.getLinha());
	prox = this->AnaLex->avancaToken();
	if (prox.getTipo() != TipoToken::identificador)
		throw string("Expected identifier after procedure declaration at line " + prox.getLinha());
    string nome = prox.getToken();
    prox = this->AnaLex->avancaToken();
    vector<Parametro> params;
    if (prox.getTipo() == TipoToken::abreParenteses)
    {
        prox = this->AnaLex->avancaToken();
        while (prox.getTipo() != TipoToken::fechaParenteses)
        {
            if (prox.getTipo() == TipoToken::identificador)
            {
                bool mesmoTipo = true;
                forward_list<Token> pars;
                while (mesmoTipo)
                {
                    pars.push_front(prox);
                    prox = this->AnaLex->avancaToken();
                    if (prox.getTipo() == TipoToken::doisPontos)
                        mesmoTipo = false;
                    else if (prox.getTipo() == TipoToken::virgula)
                        prox = this->AnaLex->avancaToken();
                    else
                        throw ("\":\" or \",\" expected at line " + prox.getLinha());
                }
                prox = this->AnaLex->avancaToken();
                if (prox.getTipo() == TipoToken::inteiro)
                {
                    for (auto it = pars.cbegin(); it != pars.cend(); it++)
                    {
                        Parametro p ((*it).getToken(), TipoVariavel::integer ,this->nivel);
                        params.push_back(p);
                        this->ts.inserirSimbolo(p);

                    }
                    pars.clear();
                }
                else if  (prox.getTipo() == TipoToken::booleano)
                {
                    for (auto it = pars.cbegin(); it != pars.cend(); it++)
                    {
                        Parametro p ((*it).getToken(), TipoVariavel::boolean ,this->nivel);
                        params.push_back(p);
                        this->ts.inserirSimbolo(p);
                    }
                    pars.clear();
                }
                else
                    throw string ("Variable type expected at line " + prox.getLinha());
                prox = this->AnaLex->avancaToken();
                if (prox.getTipo() == TipoToken::pontoEVirgula)
                    prox = this->AnaLex->avancaToken();
                else if (prox.getTipo() != TipoToken::fechaParenteses)
                    throw ("\")\" expected after variable declaration at line " + prox.getLinha());
            }
            else
                throw ("Identifier expected at line " + prox.getLinha());
        }
        if (prox.getTipo() != TipoToken::fechaParenteses)
            throw string ("\")\" expected at line " + prox.getLinha());
    }
	prox = this->AnaLex->avancaToken();
	if (prox.getTipo() != TipoToken::pontoEVirgula)
		throw ("\";\" expected at line " + prox.getLinha());
	prox = this->AnaLex->proximoToken();
	if (prox.getTipo() == TipoToken::variavel)
		this->compilaDeclaracaoDeVariavel();
	bool fim = false;
	while (!fim) // TODOS OS PROCEDIMENTOS E FUNÇÕES PRECEDEM O CÓDIGO PRINCIPAL
	{
		switch (prox.getTipo())
		{
        case TipoToken::procedimento:
            this->compilaDeclaracaoDeProcedimento();
            break;
        case TipoToken::funcao:
            this->compilaDeclaracaoDeFuncao();
            break;
        default :
            fim = true;
		}
		prox = this->AnaLex->proximoToken();
	}
	this->compilaComandoComposto();
	prox = this->AnaLex->avancaToken();
	if (prox.getTipo() != TipoToken::pontoEVirgula)
		throw string("\";\" after end of procedure at line " + prox.getLinha());
    this->nivel--;
    this->ts.inserirSimbolo(Procedimento(nome, this->nivel, params));
}

void AnalisadorSintatico::compilaDeclaracaoDeFuncao() throw (string)
{
    this->nivel++;
	Token prox = this->AnaLex->avancaToken();
	if (prox.getTipo() != TipoToken::procedimento)
		throw string("\"procedure\" expected at line " + prox.getLinha());
	prox = this->AnaLex->avancaToken();
	if (prox.getTipo() != TipoToken::identificador)
		throw string("Expected identifier after procedure declaration at line " + prox.getLinha());
    string nome = prox.getToken();
    prox = this->AnaLex->avancaToken();
    vector<Parametro> params;
    if (prox.getTipo() == TipoToken::abreParenteses)
    {
        prox = this->AnaLex->avancaToken();
        while (prox.getTipo() != TipoToken::fechaParenteses)
        {
            if (prox.getTipo() == TipoToken::identificador)
            {
                bool mesmoTipo = true;
                forward_list<Token> pars;
                while (mesmoTipo)
                {
                    pars.push_front(prox);
                    prox = this->AnaLex->avancaToken();
                    if (prox.getTipo() == TipoToken::doisPontos)
                        mesmoTipo = false;
                    else if (prox.getTipo() == TipoToken::virgula)
                        prox = this->AnaLex->avancaToken();
                    else
                        throw ("\":\" or \",\" expected at line " + prox.getLinha());
                }
                prox = this->AnaLex->avancaToken();
                if (prox.getTipo() == TipoToken::inteiro)
                {
                    for (auto it = pars.cbegin(); it != pars.cend(); it++)
                    {
                        Parametro p ((*it).getToken(), TipoVariavel::integer ,this->nivel);
                        params.push_back(p);
                        this->ts.inserirSimbolo(p);

                    }
                    pars.clear();
                }
                else if  (prox.getTipo() == TipoToken::booleano)
                {
                    for (auto it = pars.cbegin(); it != pars.cend(); it++)
                    {
                        Parametro p ((*it).getToken(), TipoVariavel::boolean ,this->nivel);
                        params.push_back(p);
                        this->ts.inserirSimbolo(p);
                    }
                    pars.clear();
                }
                else
                    throw string ("Variable type expected at line " + prox.getLinha());
                prox = this->AnaLex->avancaToken();
                if (prox.getTipo() == TipoToken::pontoEVirgula)
                    prox = this->AnaLex->avancaToken();
                else if (prox.getTipo() != TipoToken::fechaParenteses)
                    throw ("\")\" expected after variable declaration at line " + prox.getLinha());
            }
            else
                throw ("Identifier expected at line " + prox.getLinha());
        }
        if (prox.getTipo() != TipoToken::fechaParenteses)
            throw string ("\")\" expected at line " + prox.getLinha());
    }
	prox = this->AnaLex->avancaToken();
	if (prox.getTipo() != TipoToken::doisPontos)
        throw ("\":\" expected at line " + prox.getLinha());
    prox = this->AnaLex->avancaToken();
    switch (prox.getTipo())
    {
    case TipoToken::inteiro:
        this->ts.inserirSimbolo(Funcao(nome,TipoVariavel::integer,this->nivel-1,params));
        break;
    case TipoToken::booleano:
        this->ts.inserirSimbolo(Funcao(nome,TipoVariavel::boolean,this->nivel-1,params));
        break;
    default:
        throw string ("Return type expected at line " + prox.getLinha());
    }
	if (prox.getTipo() != TipoToken::pontoEVirgula)
		throw ("\";\" expected at line " + prox.getLinha());
	prox = this->AnaLex->proximoToken();
	if (prox.getTipo() == TipoToken::variavel)
		this->compilaDeclaracaoDeVariavel();
	bool fim = false;
	while (!fim) // TODOS OS PROCEDIMENTOS E FUNÇÕES PRECEDEM O CÓDIGO PRINCIPAL
	{
		switch (prox.getTipo())
		{
        case TipoToken::procedimento:
            this->compilaDeclaracaoDeProcedimento();
            break;
        case TipoToken::funcao:
            this->compilaDeclaracaoDeFuncao();
            break;
        default :
            fim = true;
		}
		prox = this->AnaLex->proximoToken();
	}
	this->compilaComandoComposto();
	prox = this->AnaLex->avancaToken();
	if (prox.getTipo() != TipoToken::pontoEVirgula)
		throw string("\";\" after end of procedure at line " + prox.getLinha());
    this->nivel--;
}

void AnalisadorSintatico::compilaDeclaracaoDePP() throw (string)
{
    this -> compilaComandoComposto();
    Token prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::ponto)
        //erros.push_back("\".\" expected at line " + prox.getLinha());
        throw string ("\".\" expected at line " + prox.getLinha());
}


void AnalisadorSintatico::compilaSe () throw (string)
{
	Token prox = this->AnaLex->avancaToken();
	if (prox.getTipo() != TipoToken::se)
		throw string ("\"if\" expected at line " + prox.getLinha());
	tipo = this->compilarExpressao();
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

void AnalisadorSintatico::compilaDeclaracaoDeWhile() throw (string)
{
    Token prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::enquanto)
        throw ("\"while\" expected at line " + prox.getLinha());
	tipo = this->compilarExpressao();
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
            throw string ("How did you even manage to come up with this?");
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



/*void AnalisadorSintatico::compilaDeclaracaoDeProcedimento() throw (string)
{
    nivel++;
    Token prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::procedimento)
        throw string ("\"procedure\" expected at line " + prox.getLinha());
    Token ult = prox;
    prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::identificador)
        throw string ("Identifier expected at line " + ult.getLinha());
    string nome = prox.getToken();
    ult = prox;
    prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::abreParenteses)
        throw string ("\"(\" expected at line " + ult.getLinha());
    ult = prox;
    prox = this->AnaLex->avancaToken();
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
                prox = this->AnaLex->avancaToken();
                if (prox.getTipo() == TipoToken::doisPontos)
                    mesmoTipo = false;
                else if (prox.getTipo() == TipoToken::virgula)
                {
                    ult = prox;
                    prox = this->AnaLex->avancaToken();
                }
                else
                    throw ("\":\" or \",\" expected at line " + ult.getLinha());
            }
            ult = prox;
            prox = this->AnaLex->avancaToken();
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
            prox = this->AnaLex->avancaToken();
            if (prox.getTipo() == TipoToken::pontoEVirgula)
            {
                ult = prox;
                prox = this->AnaLex->avancaToken();
            }
            else if (prox.getTipo() != TipoToken::fechaParenteses)
                throw ("\")\" expected after variable declaration at line " + ult.getLinha());
        }
    }
    if (prox.getTipo() != TipoToken::fechaParenteses)
        throw string ("\")\" expected at line " + ult.getLinha());

    ult = prox;
    prox = this->AnaLex->avancaToken();
    if (prox.getTipo() != TipoToken::pontoEVirgula)
        throw string ("\";\" expected at line after procedure declaration" + ult.getLinha());
    ult = prox;
    prox = this->AnaLex->avancaToken();
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
                prox = this->AnaLex->avancaToken();
                if (prox.getTipo() == TipoToken::doisPontos)
                    mesmoTipo = false;
                else if (prox.getTipo() == TipoToken::virgula)
                {
                    ult = prox;
                    prox = this->AnaLex->avancaToken();
                }
                else
                    throw ("\":\" or \",\" expected at line " + ult.getLinha());
            }
            ult = prox;
            prox = this->AnaLex->avancaToken();
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
            prox = this->AnaLex->avancaToken();
            if (prox.getTipo() == TipoToken::pontoEVirgula)
            {
                ult = prox;
                prox = this->AnaLex->avancaToken();
            }
            else if (prox.getTipo() != TipoToken::comeco)
                throw ("\"begin\" expected after variable declaration at line " + ult.getLinha());
        }
    }

    if (prox.getTipo() != TipoToken::comeco)
        throw string ("\"begin\" expected at line " + prox.getLinha());


    nivel--;
    ts.inserirSimbolo(Procedimento(nome,nivel,params));
}
