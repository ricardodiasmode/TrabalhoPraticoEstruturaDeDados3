#include "Arvore.h"
#include <fstream>
#include <iostream>

#include <string>

int main(int argc, char* argv[]) 
{
    using namespace std;

    ifstream InfoFile(argv[1]);
    if (!InfoFile)
    {
        cout << "Impossivel abrir info file";
        return -1;
    }

    Arvore* MinhaArvore = new Arvore();

    // Loop que verifica cada linha do arquivo e qual comando foi passado
    char* StringComando = new char[2];
    while (InfoFile >> StringComando)
    {
        if (StringComando[0] == 'A' && StringComando[1] == ':')
            MinhaArvore->CarregarArvore(&InfoFile);
        else if (StringComando[0] == 'D' && StringComando[1] == ':')
            MinhaArvore->Decodificar(&InfoFile);
        else if (StringComando[0] == 'C' && StringComando[1] == ':')
            MinhaArvore->Codificar(&InfoFile);
    }

    delete MinhaArvore;
    InfoFile.close();
    return 0;
}