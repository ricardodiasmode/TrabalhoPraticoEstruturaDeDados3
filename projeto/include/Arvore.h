#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <fstream>
#include <iostream>

class No
{
public:
    No();
    No(int);

private:
    int Item;
    No* esq;
    No* dir;

    friend class Arvore;
};

class Arvore 
{
public:
    Arvore();
    ~Arvore();

    // Le a linha do arquivo e cria a arvore de acordo com os dados recebidos
    void CarregarArvore(std::ifstream* Arquivo);
    // Le a linha do arquivo e transforma o codigo lido em uma string seguindo a arvore montada
    void Decodificar(std::ifstream* Arquivo);
    // Le a proxima linha do arquivo, que deve ser uma string, e transforma em um codigo que leva ao caminho da arvore
    void Codificar(std::ifstream* Arquivo);
    // Chama o InsereRecursivo
    void Insere(int Item);
    // Limpa a arvore
    void Limpa();
    // Retorna a raiz
    No* GetRaiz() { return Raiz; }
    // Printa a arvore no caminhamento Central
    void InOrdem(No* CurrentNode);
    // Printa a arvore no caminhamento PosOrdem
    void PosOrdem(No* CurrentNode);

private:
    // Insere recursivamente um node na arvore
    No* InsereRecursivo(No* CurrentNode, int Item);
    // Apaga recursivamente todos os nodes da arvore
    void ApagaRecursivo(No* CurrentNode);
    No* Raiz;
};

#endif