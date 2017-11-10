#include <iostream>
#include<string>
#include "AnalisadorLexico.h"

const string nomeArq("../../teste.txt");

using namespace std;

int main()
{
    AnalisadorLexico a(nomeArq);

    return 0;
}
