#ifndef TOKEN
#define TOKEN

#include <string>

using namespace std;

enum class TokenType{
     PROGRAM,           // Program
     VARIABLE,          // var
     BEGIN,             // Begin
     END,               // End
     IF,                // if
     WHILE,             // while
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
     NOT,               // not -- operadores binários e lógicos são iguais
     OR,                // or
     AND,               // and
     XOR,               // xor
     RIGHT_PARENTHESIS, // (
     LEFT_PARENTHESIS,  // )
     PERIOD,            // . -- identifica o fim do programa
     COMMA,             // , -- divide declaração de variáveis
     SEMICOLON,         // ;
     WRITE,             // write
     READ,              // read
     TRUE,              // true
     FALSE,             // false
     IDENTIFIER,        // nome da var ou função que não as duas acima
     NUMBER,            // número constante no meio do código
     UNKNOWN            // símbolo que não consta acima
};

class Token {
private:
    TokenType type;
    string token;
    static vector<string> symbols;
    int line;

public:
    Token(string, int) throw ();
    string getToken() const throw ();
    TokenType getType() const throw ();
    int getLine() const throw ();
};

#endif // TOKEN
