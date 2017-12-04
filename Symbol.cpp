#include "Symbol.h"

using namespace std;

//SIMBOLO

Symbol::Symbol(const string& name, VariableType returnType) throw(string)
    : Symbol(name, returnType, nullptr) {}

Symbol::Symbol(const string& name, VariableType returnType, const vector<Symbol>* const params) throw(string)
    : name(name) {
    this->returnType = returnType;
    if (params != nullptr) {
        for (auto it =  params->cbegin(); it != params->cend(); it++)
            if (it->getType() != SymbolType::VARIABLE)
                throw string("Function or procedure parameter must be variable");

        this->params = new vector<Symbol>(*params);
    }
    else
        this->params = nullptr;
}

Symbol::Symbol(const Symbol& outro) {
    *this = outro;
}

Symbol Symbol::operator=(const Symbol& outro) {
    this->name = outro.name;
    this->returnType = outro.returnType;
    this->params = outro.params;
}

Symbol::~Symbol() {
    delete this->params;
}

string Symbol::getName() const throw () {
    return string(this->name);
}

SymbolType Symbol::getType() const throw() {
    if (this->returnType == VariableType::VOID)
        return SymbolType::PROCEDURE;
    if (this->params == nullptr)
        return SymbolType::VARIABLE;

    return SymbolType::FUNCTION;
}

VariableType Symbol::getReturnType() const {
    return this->returnType;
}

VariableType Symbol::getParamType(unsigned int i) const throw(string) {
    return this->getParam(i).getReturnType();
}

Symbol Symbol::getParam(unsigned int i) const throw(string) {
    if (this->params == nullptr)
        throw string("Cannot read variable params");
    if (this->params->size() < i)
        throw string ("Index out of bounds");

    return Symbol(this->params->at(i));
}

bool Symbol::operator!=(const Symbol& other) const throw () {
    return !this->operator==(other);
}

bool Symbol::operator==(const Symbol& other) const throw () {
    return this->name != other.name;
}
