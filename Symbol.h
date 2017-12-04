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
    PROCEDURE,
    FUNCTION
};

class Symbol
{
protected:
    string name;
    VariableType returnType;
    vector<Symbol>* params;
public:
    Symbol(const string& name, VariableType returnType);
    Symbol(const string& name, VariableType returnType, const vector<Symbol> * const params);
    Symbol(const Symbol&);
    Symbol operator=(const Symbol&);
    virtual ~Symbol();

    string getName() const throw ();
    SymbolType getType() const throw();
    Symbol getParam(unsigned int) const throw(string);
    bool operator== (const Symbol&) const throw ();
    bool operator!= (const Symbol&) const throw ();
};

#endif // SYMBOL_INCLUDED
