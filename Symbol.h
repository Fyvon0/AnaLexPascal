#ifndef SYMBOL_INCLUDED
#define SYMBOL_INCLUDED

#include <string>
#include <vector>

using namespace std;

enum class VariableType {
    BOOLEAN,
    INTEGER,
    VOID
};

enum class SymbolType {
    VARIABLE,
    FUNCTION,
    NULL
};

class Symbol
{
protected:
    string name;
public:
    string getName() const throw ();
    virtual bool operator== (Symbol) const throw ();
    virtual SymbolType getType();
    bool operator!= (Symbol) const throw ();
};

class Variable : public Symbol
{
private:
    VariableType tipo;
public:
    Variable (string, VariableType) throw (string);
    VariableType getTipoVariavel () const throw ();
    bool operator== (Symbol) const throw ();
    bool operator!= (Symbol) const throw ();
};

class Funcao : public Symbol
{
private:
    vector<Variable> params;
    VariableType returnType;
public:
    Funcao (string, TipoVariavel, vector<Variable>) throw ();
    unsigned int getParamCount () const throw ();
    VariableType getParamType (unsigned int) const throw (string);
    VariableType getReturnType () const throw ();
    bool operator== (Symbol) const throw ();
    bool operator!= (Symbol) const throw ();
};

#endif // SYMBOL_INCLUDED
