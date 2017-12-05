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

void Parser::throwUndeclared(string name, int line) throw (string) {
    throw string("Reference to undeclared identifier "+name+" at line " +/*std::*/to_string(line));
}

void Parser::throwIncompatibleType(int line) throw (string) {
    throw string("Incompatible types at line "+to_string(line));
}

void Parser::throwWtf() throw (string) {
    throw string("How did you even do dis boi?");
}

void Parser::compile() throw (string) {
    compileProgramStart();
    //cout << TokenTypeNames[(int)this->lex.peekToken().getType()];
    if (this->lex.peekToken().getType() == TokenType::VARIABLE)
        compileVariableDeclaration();
    if (this->lex.peekToken().getType() == TokenType::PROCEDURE)
        this->compileProcedureDeclaration();
}

void Parser::compileProgramStart () throw (string) {
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

void Parser::compileVariableDeclaration () throw (string) {
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

void Parser::compileProcedureDeclaration () throw (string) {
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
	while (!end) // TODOS OS PROCEDIMENTOS E FUN��ES PRECEDEM O C�DIGO PRINCIPAL
	{
		switch (next.getType())
		{
        case TokenType::PROCEDURE:
            this->compileProcedureDeclaration();
            break;
        case TokenType::FUNCTION:
            this->compileFunctionDeclaration();
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

void Parser::compileFunctionDeclaration () throw (string) {
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
    if (next.getType() != TokenType::COLON)
        this->throwExpected(TokenType::COLON, next.getLine(), next.getType());

    VariableType type;
    next = this->lex.nextToken();
    if (next.getType() == TokenType::INTEGER)
        type = VariableType::INTEGER;
    else if(next.getType() == TokenType::BOOLEAN)
        type = VariableType::BOOLEAN;
    else
        this->throwExpected(TokenType::VARIABLE, next.getLine(), next.getType());


    next = this->lex.nextToken();
    if (next.getType() != TokenType::SEMICOLON)
        this->throwExpected(TokenType::SEMICOLON, next.getLine(), next.getType());

    this->st.insertSymbol(Symbol(name, type, &params));
    for (auto it = params.cbegin(); it != params.cend(); it++)
        this->st.insertSymbol(*it);

    if (this->lex.peekToken().getType() == TokenType::VARIABLE)
        this->compileVariableDeclaration();

    next = this->lex.peekToken();
    bool end = false;
	while (!end) // TODOS OS PROCEDIMENTOS E FUN��ES PRECEDEM O C�DIGO PRINCIPAL
	{
		switch (next.getType())
		{
        case TokenType::PROCEDURE:
            this->compileProcedureDeclaration();
            break;
        case TokenType::FUNCTION:
            this->compileFunctionDeclaration();
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

void Parser::compileCompoundCommand () throw (string) {
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
    Token next = this->lex.peekToken();
    switch (next.getType())
    {
    case TokenType::IDENTIFIER:
    {
        Symbol *s = this->st.getSymbol(next.getToken());
        if (s == nullptr)
            throwUndeclared(next.getToken(), next.getLine());
        switch(s->getType())
        {
        case SymbolType::VARIABLE:
            this->compileAttr();
            break;
        case SymbolType::FUNCTION:
            this->compileFuncCall();
            break;
        }
        break;
    }
    case TokenType::IF:
    {
        //this->compileIf();
        break;
    }
    case TokenType::WHILE:
    {
        //this->compileWhile();
        break;
    }
    case TokenType::WRITE:
    {
        //this->compileWrite();
        break;
    }
    case TokenType::READ:
    {
        //this->compileRead();
        break;
    }
    default:
        this->throwExpected(TokenType::VARIABLE, next.getLine(), next.getType());
        break;
    }


    next = this->lex.nextToken();
    if (next.getType() != TokenType::SEMICOLON)
        throwExpected(TokenType::SEMICOLON, next.getLine(), next.getType());
}

VariableType Parser::compileFuncCall () throw (string) {
    Token next = this->lex.nextToken();
    Symbol *func = this->st.getSymbol(next.getToken());
    if (func == nullptr)
        throwUndeclared(next.getToken(), next.getLine());

    if (func->getType() != SymbolType::FUNCTION)
        throwWtf();

    next = this->lex.nextToken();
    if (next.getType() == TokenType::LEFT_PARENTHESIS)
    {
        vector<Symbol> params = *func->getParams();

        // TODO: Refazer isso aqui
        for (auto i = params.cbegin(); i != params.cend(); i++) {
            if (i->getReturnType() != this->compileTypedSymbol())
                throwIncompatibleType(next.getLine());

            next = this->lex.nextToken();
            if (next.getType() != TokenType::COMMA) // TODO: Virgula no final mas fodase
                throwExpected(TokenType::COMMA, next.getLine(), next.getType());
        }

        next = this->lex.nextToken();
        if (next.getType() != TokenType::RIGHT_PARENTHESIS)
            throwExpected(TokenType::RIGHT_PARENTHESIS, next.getLine(), next.getType());
    }
    else if (func->getParamCount() > 0)
        throw string("No such implementation for call to method " + func->getName() + " was found as in line " + to_string(next.getLine()));

    return func->getReturnType();
}

void Parser::compileAttr() throw (string) {
    Token next = this->lex.nextToken();
    if (next.getType() != TokenType::IDENTIFIER)
        throwWtf();

    Symbol* s = this->st.getSymbol(next.getToken());
    if (s == nullptr)
        throwUndeclared(s->getName(), next.getLine());

    if (s->getType() != SymbolType::VARIABLE)
        throwWtf();

    VariableType type = s->getReturnType();

    next = this->lex.nextToken();
    if (next.getType() != TokenType::ATTRIBUTION)
        throwExpected(TokenType::ATTRIBUTION, next.getLine(), next.getType());

    if (type != this->compileTypedSymbol())
        throwIncompatibleType(next.getLine());
}

VariableType Parser::compileTypedSymbol() throw (string) {
    Token next = this->lex.nextToken();
    if (next.getType() == TokenType::TRUE || next.getType() == TokenType::FALSE)
        return VariableType::BOOLEAN;
    if (next.getType() == TokenType::INTEGER)
        return VariableType::INTEGER;

    if (next.getType() != TokenType::IDENTIFIER)
        throwExpected(TokenType::IDENTIFIER, next.getLine(), next.getType());

    Symbol* s = this->st.getSymbol(next.getToken());
    if (s == nullptr)
        throwUndeclared(next.getToken(), next.getLine());

    if (s->getType() == SymbolType::FUNCTION) {
        this->lex.ungetToken();
        this->compileFuncCall();
    }

    return s->getReturnType();
}

void Parser::compileRead() throw (string)
{
    Token next = this->lex.nextToken();
    if (next.getType() != TokenType::READ)
        this->throwExpected(TokenType::READ, next.getLine(), next.getType());

    next = this->lex.nextToken();
    if (next.getType() != TokenType::LEFT_PARENTHESIS)
        this->throwExpected(TokenType::LEFT_PARENTHESIS, next.getLine(), next.getType());

    next = this->lex.nextToken();
    if (next.getType() != TokenType::IDENTIFIER)
        this->throwExpected(TokenType::IDENTIFIER, next.getLine(), next.getType());

    Symbol *s = this->st.getSymbol(next.getToken());
    if (s == nullptr)
        this->throwUndeclared(next.getToken(), next.getLine());
    if (s->getType() != SymbolType::VARIABLE || s->getReturnType() != VariableType::INTEGER)
        this->throwExpected(TokenType::INTEGER, next.getLine(),next.getType());

    next = this->lex.nextToken();
    if (next.getType() != TokenType::RIGHT_PARENTHESIS)
        this->throwExpected(TokenType::RIGHT_PARENTHESIS, next.getLine(), next.getType());

    next = this->lex.nextToken();
    if (next.getType() != TokenType::SEMICOLON)
        this->throwExpected(TokenType::SEMICOLON, next.getLine(), next.getType());
}
