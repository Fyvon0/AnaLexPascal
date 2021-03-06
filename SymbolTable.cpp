#include <typeinfo>

#include "SymbolTable.h"

SymbolTable::SymbolTable() throw (): currentScope(0) {
    this->symbols.push_back(vector<Symbol*>()); // insere o primeiro vetor na lista
}

void SymbolTable::insertSymbol (const Symbol& s) throw (string)
{
    /*
    if (this->getSymbol(s.getName()) != nullptr)
        throw string ("Repeated declaration of identifier " + s.getName());
        */
    for (auto itSymb = symbols.back().cbegin(); itSymb != symbols.back().cend(); itSymb++)
        if ((*itSymb)->getName() == s.getName())
            throw string ("Repeated declaration of identifier " + s.getName());

    this->symbols.back().push_back(new Symbol(s));

    if (s.getType() == SymbolType::FUNCTION)
    {
        this->currentScope++;
        this->symbols.push_back(vector<Symbol*>());
    }
}

Symbol* SymbolTable::getSymbol (const string& name) const throw ()
{
    // Escopo local
    for (auto itSymb = this->symbols.back().cbegin(); itSymb != this->symbols.back().cend(); itSymb++)
        if ((*itSymb)->getName() == name)
            return new Symbol(*(*itSymb));

    // Escopo global
    for (auto itSymb = this->symbols[0].cbegin(); itSymb != this->symbols[0].cend(); itSymb++)
        if ((*itSymb)->getName() == name)
            return new Symbol(*(*itSymb));

    return nullptr;
}

void SymbolTable::clearCurrentScope() throw (string)
{
    if (this->symbols.empty())
        throw string ("Invalid end of scope");
    this->symbols.pop_back();
    this->currentScope--;
}

/*
TabelaDeSimbolos::TabelaDeSimbolos() {
    this->ultimoNivel = 0;
}

void TabelaDeSimbolos::voltarNivel() throw (string) {
    if (this->ultimoNivel <= 0)
        throw string ("N�o pode voltar mais um n�vel");

    set<Simbolo>::iterator b, e;
    bool achouComeco = false;
    for (set<Simbolo>::iterator it = this->simbolos.cbegin(); it != this->simbolos.cend(); it++)
        if (!achouComeco && it->getNivel() == this->ultimoNivel)
            b = it;
        else if (achouComeco && it->getNivel() != this->ultimoNivel) {
            e = it;
            break;
        }

    this->simbolos.erase(b, e);
    this->ultimoNivel--;
}

void TabelaDeSimbolos::avancarNivel() throw() {
    this->ultimoNivel++;
}

bool TabelaDeSimbolos::existe(Simbolo s) const throw () {
    return this->simbolos.find(s) == this->simbolos.end();
}

void TabelaDeSimbolos::inserirSimbolo(Simbolo s) throw (string) {
    if (existe(s))
        throw string ("N�o pode inserir s�mbolo repetido.");
    this->inserirSimbolo(s, this->ultimoNivel);
}

void TabelaDeSimbolos::inserirSimbolo(Simbolo s, char nivel) throw (string) {
    if (existe(s))
        throw string ("N�o pode inserir s�mbolo repetido.");
    s.setNivel(nivel);
    this->simbolos.insert(s);
}

char TabelaDeSimbolos::getUltimoNivel() const throw () {
    return this->ultimoNivel;
}

Simbolo TabelaDeSimbolos::getSimbolo(string nome) const throw (string) {
    for (auto it = simbolos.cbegin(); it != simbolos.cend(); it++)
        if (it->getNivel() != this->ultimoNivel)
            continue;
        else if (it->getNome() == nome)
            return *it;

    throw string ("Tipo n�o declarado");
}

TipoSimbolo TabelaDeSimbolos::getTipo(string nome) throw (){
    for (auto it = simbolos.begin(); it != simbolos.end(); it++)
        if (it->getNivel() != this->ultimoNivel) // S� para s�mbolos do n�vel atual
            continue;
        else if (it->getNome() == nome)
        {
            if (typeid(*it) == typeid(Variavel))
                return TipoSimbolo::Variavel;
            if (typeid(*it) == typeid(Parametro))
                return TipoSimbolo::Parametro;
            if (typeid(*it) == typeid(Procedimento))
                return TipoSimbolo::Procedimento;
            if (typeid(*it) == typeid(Funcao))
                return TipoSimbolo::Funcao;
        }
    return TipoSimbolo::Nenhum;
}
*/

