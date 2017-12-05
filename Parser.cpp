#include <sstream>
#include <forward_list>

#include "Parser.h"


const string TokenTypeNames[] = {"PROGRAM","VAR","BEGIN","END","IF","WHILE","INTEGER","BOOLEAN","COLON","ATTRIBUTION","SUM",
                                 "SUBTRACTION","MULTIPLICATION","DIVISION","MODULE","PROCEDURE","FUNCTION","=","!=",">","<",
                                 ">=","<=","NOT","OR","AND","XOR","(",")",".",",",";","WRITE","READ","TRUE","FALSE",
                                 "IDENTIFIER","CONSTANT","UNKNOWN"};

Parser::Parser(string path) throw () : lex(path), st() {}


template <typename T>
std::string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}

void Parser::throwExpected(TokenType expected, int line, TokenType found) throw (string) {
    throw string ("\"" + TokenTypeNames[(int)expected] +
                  "\" expected at line " +
                  /*std::*/to_string(line) +
                  " but \"" +
                  TokenTypeNames[(int)found] +
                  "\" found instead.");
}

void Parser::compile() throw (string) {
    compileProgramStart();
    //cout << TokenTypeNames[(int)this->lex.peekToken().getType()];
    if (this->lex.peekToken().getType() == TokenType::VARIABLE)
        compileVariableDeclaration();
    if (this->lex.peekToken().getType() == TokenType::PROCEDURE)
        this->compileProcedureDeclaration();
}

void Parser::compileProgramStart () throw (string)
{
    Token next = this->lex.nextToken();
    if (next.getType() != TokenType::PROGRAM)
        this->throwExpected(TokenType::PROGRAM, next.getLine(), next.getType());

    next = this->lex.nextToken();
    if (next.getType() != TokenType::IDENTIFIER)
        this->throwExpected(TokenType::IDENTIFIER, next.getLine(), next.getType());

    next = this->lex.nextToken();
    if (next.getType() != TokenType::SEMICOLON)
        this->throwExpected(TokenType::SEMICOLON, next.getLine(), next.getType());
}

void Parser::compileVariableDeclaration () throw (string)
{
    Token next = this->lex.nextToken();
    if (next.getType() != TokenType::VARIABLE)
        this->throwExpected(TokenType::VARIABLE, next.getLine(), next.getType());

    next = this->lex.nextToken();
    if (next.getType() != TokenType::IDENTIFIER)
        this->throwExpected(TokenType::IDENTIFIER, next.getLine(), next.getType());

    while (true)
    {
        bool sameType = true;
        forward_list<Token> pars;
        while (sameType)
        {
            pars.push_front(next);
            next = this->lex.nextToken();
            if (next.getType() == TokenType::COLON)
                sameType = false;
            else if (next.getType() == TokenType::COMMA)
                next = this->lex.nextToken();
            else
                this->throwExpected(TokenType::COMMA, next.getLine(), next.getType());
        }
        next = this->lex.nextToken();
        if (next.getType() ==TokenType::INTEGER)
        {
            for (auto it = pars.cbegin(); it != pars.cend(); it++)
            {
                const Symbol p (it->getToken(), VariableType::INTEGER);
                this->st.insertSymbol(p);
            }
            pars.clear();
        }
        else if  (next.getType() == TokenType::BOOLEAN)
        {
            for (auto it = pars.cbegin(); it != pars.cend(); it++)
            {
                const Symbol p(it->getToken(), VariableType::BOOLEAN);
                this->st.insertSymbol(p);
            }
            pars.clear();
        }
        else
            this->throwExpected(TokenType::VARIABLE, next.getLine(), next.getType());
        next = this->lex.nextToken();
        if (next.getType() == TokenType::SEMICOLON)
        {
            if (this->lex.currentToken().getType() != TokenType::IDENTIFIER)
                break;
            next = this->lex.nextToken();
        }
        else
            this->throwExpected(TokenType::SEMICOLON, next.getLine(), next.getType());
    }
}

void Parser::compileProcedureDeclaration () throw (string)
{
    Token next = this->lex.nextToken();
    if (next.getType() != TokenType::PROCEDURE)
        this->throwExpected(TokenType::PROCEDURE, next.getLine(), next.getType());

    next = this->lex.nextToken();
    if (next.getType() != TokenType::IDENTIFIER)
        this->throwExpected(TokenType::IDENTIFIER, next.getLine(), next.getType());
    string name = next.getToken();

    next = this->lex.nextToken();
    if (next.getType() != TokenType::LEFT_PARENTHESIS)
        this->throwExpected(TokenType::LEFT_PARENTHESIS, next.getLine(), next.getType());

    next = this->lex.nextToken();
    vector<Symbol> params;
    if (next.getType() != TokenType::RIGHT_PARENTHESIS)
    {
        if (next.getType() == TokenType::VARIABLE || next.getType() == TokenType::IDENTIFIER)
        {
            while (true)
            {
                bool sameType = true;
                forward_list<Token> pars;
                while (sameType)
                {
                    pars.push_front(next);
                    next = this->lex.nextToken();
                    if (next.getType() == TokenType::COLON)
                        sameType = false;
                    else if (next.getType() == TokenType::COMMA)
                        next = this->lex.nextToken();
                    else
                        this->throwExpected(TokenType::COMMA, next.getLine(), next.getType());
                }
                next = this->lex.nextToken();
                if (next.getType() ==TokenType::INTEGER)
                {
                    for (auto it = pars.cbegin(); it != pars.cend(); it++)
                    {
                        const Symbol p (it->getToken(), VariableType::INTEGER);
                        params.push_back(p);
                    }
                    pars.clear();
                }
                else if  (next.getType() == TokenType::BOOLEAN)
                {
                    for (auto it = pars.cbegin(); it != pars.cend(); it++)
                    {
                        const Symbol p(it->getToken(), VariableType::BOOLEAN);
                        params.push_back(p);
                    }
                    pars.clear();
                }
                else
                    this->throwExpected(TokenType::VARIABLE, next.getLine(), next.getType());
                next = this->lex.nextToken();
                if (next.getType() == TokenType::SEMICOLON || next.getType() == TokenType::RIGHT_PARENTHESIS)
                {
                    if (this->lex.peekToken().getType() != TokenType::IDENTIFIER)
                        break;
                    next = this->lex.nextToken();
                }
                else
                    this->throwExpected(TokenType::RIGHT_PARENTHESIS, next.getLine(), next.getType());
            }
        }
        else
            this->throwExpected(TokenType::RIGHT_PARENTHESIS, next.getLine(), next.getType());
    }

    next = this->lex.nextToken();
    if (next.getType() != TokenType::SEMICOLON)
        this->throwExpected(TokenType::SEMICOLON, next.getLine(), next.getType());

    this->st.insertSymbol(Symbol(name, VariableType::VOID, &params));
    for (auto it = params.cbegin(); it != params.cend(); it++)
        this->st.insertSymbol(*it);

    if (this->lex.peekToken().getType() == TokenType::VARIABLE)
        this->compileVariableDeclaration();

    next = this->lex.peekToken();
    bool end = false;
	while (!end) // TODOS OS PROCEDIMENTOS E FUNÇÕES PRECEDEM O CÓDIGO PRINCIPAL
	{
		switch (next.getType())
		{
        case TokenType::PROCEDURE:
            this->compileProcedureDeclaration();
            break;
        case TokenType::FUNCTION:
            //this->compileFunctionDeclaration();
            break;
        case TokenType::BEGIN :
            end = true;
            break;
        default:
            this->throwExpected(TokenType::BEGIN, next.getLine(), next.getType());
		}
		next = this->lex.peekToken();
	}
	this->compileCompoundCommand();
	next = this->lex.nextToken();
	if (next.getType() != TokenType::SEMICOLON)
        this->throwExpected(TokenType::SEMICOLON, next.getLine(), next.getType());
    this->st.clearCurrentScope();
}

void Parser::compileCompoundCommand () throw (string)
{
    Token next = this->lex.nextToken();
    if (next.getType() != TokenType::BEGIN)
        this->throwExpected(TokenType::BEGIN, next.getLine(), next.getType());

    while (this->lex.peekToken().getType() != TokenType::END)
        this->compileCommand();
    next = this->lex.nextToken();
    if (next.getType() != TokenType::END)
        this->throwExpected(TokenType::END, next.getLine(), next.getType());
}

void Parser::compileCommand() throw (string)
{
    Token next = this->lex.nextToken();
    if (next.getType() == TokenType::IDENTIFIER)
    {
        Symbol *s = this->st.getSymbol(next.getToken());
        if (s == nullptr)
            throw string("Reference to undeclared identifier " + s->getName() + " at line " + to_string(next.getLine()));
        switch(s->getType())
        {
        case SymbolType::VARIABLE:
            //this->compileAttr();
            break;
        case SymbolType::PROCEDURE:
            //this->compileProcCall();
            break;
        case SymbolType::FUNCTION:
            //this->compileFuncCall();
            break;
        }
    }
}
    /*
    params.push_back(next.getToken());
    next = this->lex.nextToken();
    if (next.getType() == TokenType::COMMA)
        for (;;)
        {
            Token ult = next;
            if (ult.getType() == TokenType::SEMICOLON && next.getType() == TokenType::IDENTIFIER)
                break;
            if ((ult.getType() == TokenType::COMMA && next.getType() == TokenType::IDENTIFIER) || (next.getType() == TokenType::COMMA && ult.getType() == TokenType::IDENTIFIER))
                continue;
            if (ult.getType() == TokenType::IDENTIFIER)
                this->throwExpected(TokenType::COMMA, next.getLine(), next.getType());
            if (ult.getType() == TokenType::COMMA)
                this->throwExpected(TokenType::IDENTIFIER, next.getLine(), next.getType());
            throw string ("ESSO NON ECZISTE!!!");
        }
    */

