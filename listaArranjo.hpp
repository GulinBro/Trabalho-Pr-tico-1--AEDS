#ifndef LISTA_A_H
#define LISTA_A_H
#include <iostream>

using namespace std;

#define MAXTAM 5

typedef int TipoApontador;

typedef struct Projeto
{
    int chave;
    char nome[50];
    int horas;
};

typedef struct ListaProjetos
{
    Projeto Item[MAXTAM];
    int Primeiro, Ultimo;
    int tamanho;
};

bool listaCriadaArranjo = false;

void criaListaVazia(ListaProjetos *lista);                              // Cria uma lista vazia
int verificaListaVazia(ListaProjetos *lista);                           // Retorna TRUE se a lista estiver vazia, FALSE caso contrário
int verificaListaCheia(ListaProjetos *lista);                           // Retorna TRUE se a lista estiver cheia, FALSE caso contrário
int insereItem(ListaProjetos *lista, Projeto item);                    // Insere ITEM (chave) na lista ListaProjetos
void imprimeLista(ListaProjetos lista);                                 // Imprime a lista
int pesquisaItem(ListaProjetos *lista, int chave);                      // Pesquisa um ITEM (chave) na lista ListaProjetos
void retiraItem(TipoApontador p, ListaProjetos *lista); // Remove um item da lista pela sua posição
int tamanhoLista(ListaProjetos *lista);                                 // Retorna o número de itens da lista

#endif
