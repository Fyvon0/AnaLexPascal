#ifndef TOKEN
#define TOKEN

#include <string>
#include <vector>

using namespace std;

enum class TokenType {
     PROGRAM,           // Program
     VARIABLE,          // var
     BEGIN,             // Begin
     END,               // End
     IF,                // if
     THEN,              // then
     ELSE,              // else
     WHILE,             // while
     DO,                // do
     REPEAT,            // repeat
     UNTIL,             // until
     INTEGER,           // integer
     BOOLEAN,           // boolean
     COLON,             // :
     ATTRIBUTION,       // :=
     SUM,               // +
     SUBTRACTION,       // -
     MULTIPLICATION,    // *
     DIVISION,          // div
     MODULE,            // mod
     PROCEDURE,         // procedure
     FUNCTION,          // function
     EQUALS,            // =
     DIFFERENT,         // <>
     BIGGER,            // >
     SMALLER,           // <
     BIGGER_EQUAL,      // >=
     SMALLER_EQUAL,     // <=
     NOT,               // not -- operadores bin�rios e l�gicos s�o iguais
     OR,                // or
     AND,               // and
     XOR,               // xor
     LEFT_PARENTHESIS,  // (
     RIGHT_PARENTHESIS, // )
     PERIOD,            // . -- identifica o fim do programa
     COMMA,             // , -- divide declara��o de vari�veis
     SEMICOLON,         // ;
     WRITE,             // write
     READ,              // read
     TRUE,              // true
     FALSE,             // false
     IDENTIFIER,        // nome da var ou fun��o que n�o as duas acima
     NUMBER,            // n�mero constante no meio do c�digo
     UNKNOWN            // s�mbolo que n�o consta acima
};

class Token {
private:
    TokenType type;
    string token;
    static vector<string> symbols;
    int line;

public:
    Token(const string&, int) throw ();
    string getToken() const throw ();
    TokenType getType() const throw ();
    int getLine() const throw ();
};

#endif // TOKEN
