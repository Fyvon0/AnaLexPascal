#ifndef DADOS
#define DADOS

#include <string>
#include <vector>

using namespace std;

enum class TipoVariavel {
    BOOLEAN,
    INTEGER
};

enum class TipoSimbolo {
    VARIAVEL,
    FUNCAO,
    PARAMETRO,
    NENHUM
};

class Simbolo
{
protected:
    string nome;
    unsigned char nivel;
    TipoSimbolo tipoSimbolo;
public:
    string getNome() const throw ();
    char getNivel() const throw ();
    char setNivel() throw (string);
    virtual bool operator== (Simbolo) const throw ();
    bool operator!= (Simbolo) const throw ();
    void setNivel(char) throw (string);
};

class Variavel : public Simbolo
{
private:
    TipoVariavel tipo;
public:
    Variavel (string, TipoVariavel, char) throw ();
    TipoVariavel getTipoVariavel () const throw ();
    bool operator== (Simbolo) const throw ();
    bool operator!= (Simbolo) const throw ();
};

class Parametro : public Simbolo
{
private:
    TipoVariavel tipo;
public:
    Parametro (string, TipoVariavel, char) throw ();
    TipoVariavel getTipoVariavel () const throw ();
    bool operator== (Simbolo) const throw ();
    bool operator!= (Simbolo) const throw ();
    bool operator== (Parametro) const throw ();
};

class Procedimento : public Simbolo
{
private:
    vector<Parametro> params;
public:
    Procedimento (string, char, vector<Parametro>) throw ();
    unsigned int getQuantidadeParametros () const throw ();
    TipoVariavel getTipoParametro (unsigned int) const throw (string);
    bool operator== (Simbolo) const throw ();
    bool operator!= (Simbolo) const throw ();
};

class Funcao : public Simbolo
{
private:
    vector<Parametro> params;
    TipoVariavel retorno;
public:
    Funcao (string, TipoVariavel, char, vector<Parametro>) throw ();
    unsigned int getQuantidadeParametros () const throw ();
    TipoVariavel getTipoParametro (unsigned int) const throw (string);
    TipoVariavel getTipoDeRetorno () const throw ();
    bool operator== (Simbolo) const throw ();
    bool operator!= (Simbolo) const throw ();
};

#endif // DADOS
