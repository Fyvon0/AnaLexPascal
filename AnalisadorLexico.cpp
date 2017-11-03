#include <string>
#include "AnalisadorLexico.h"
using namespace std;

//MACROS
#define ehOperador (s) (((s) == "+" || (s) == "-" || (s) == "*" || (s) == "div" || (s) == "/" || (s) == "mod" || (s) == "not" || (s) == "and" || (s) == "or" || (s) == "xor" || (s) == "<<" || (s) == ">>")?1:0)

string AnalisadorLexico::simbolos[] = {"Program","var","Begin","End",
                                       "if","while","integer","boolean",
                                       ":",":=","+","-","*","div","/",
                                       "mod","procedure","function","=",
                                       "<>",">","<",">=","<=","not","or",
                                       "and","xor","<<",">>","(",")",".",
                                       ",",";","write","read"};

AnalisadorLexico::AnalisadorLexico(string nomeArq)
{
    this -> myfile.open(nomeArq.c_str());
    if (!myfile.is_open())
        throw "Erro ao abrir o arquivo";
}

AnalisadorLexico::~AnalisadorLexico()
{
    this -> myfile.close();
}

//IMPLEMENTAR
TipoPedaco AnalisadorLexico::proximoPedaco()
{

}

bool AnalisadorLexico::temMaisPedacos()
{

}

string AnalisadorLexico::getNome()
{

}

int AnalisadorLexico::getValor()
{

}
