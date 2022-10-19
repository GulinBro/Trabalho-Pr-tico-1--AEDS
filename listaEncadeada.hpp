#ifndef LISTA_E_H
#define LISTA_E_H
#include <iostream>
#include "listaArranjo.hpp"

using namespace std;

typedef struct Funcionario
{
    int id;
    char nome[50];
    char endereco[50];
    int dependentes;
    ListaProjetos projetos;
} Funcionario;

typedef struct TipoElemento *Apontador;

typedef struct TipoElemento
{ // Célula
    Funcionario item;
    struct TipoElemento *prox;
} TipoElemento;

typedef struct ListaFuncionario
{
    Apontador primeiro;
    Apontador ultimo;
    int tamanho = 0;
} ListaFuncionario;

bool listaCriadaEncadeada = false;

void CriaListaVazia(ListaFuncionario *lista);
bool VerificaListaVazia(ListaFuncionario *lista);
void InsereListaPrimeiro(ListaFuncionario *lista, Funcionario *item);
void InsereListaAposElemento(ListaFuncionario *lista, Funcionario *item, int id);
void InsereListaUltimo(ListaFuncionario *lista, Funcionario *item);
void AtualizaUltimo(ListaFuncionario *lista);
void ImprimeLista(ListaFuncionario lista);
int PesquisaItem(ListaFuncionario *lista, int chave, Apontador* encontrado);
void ImprimeItem(ListaFuncionario *lista, int id);
void RemoveListaPrimeiro(ListaFuncionario *lista);
void RemoveListaUltimo(ListaFuncionario *lista);
void RemoveItemPorId(ListaFuncionario *lista, int id);
int TamanhoLista(ListaFuncionario *lista);

#endif
