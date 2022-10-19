#include <iostream>
#include <windows.h>
#include "listaArranjo.hpp"

#define MAXTAM 5

using namespace std;

void criaListaVazia(ListaProjetos *lista)
{
    lista->tamanho = 0;
    lista->Primeiro = 0;
    lista->Ultimo = lista->Primeiro;
}

int verificaListaVazia(ListaProjetos *lista)
{
    return (lista->Primeiro == lista->Ultimo);
}

int verificaListaCheia(ListaProjetos *lista)
{
    return (lista->Ultimo == MAXTAM);
}

int tamanhoLista(ListaProjetos *lista)
{
    return lista->tamanho;
}

int insereItem(ListaProjetos *lista, Projeto item)
{
    if (verificaListaCheia(lista))
    {
        return -1;
    }
    lista->Item[lista->Ultimo] = item;
    lista->tamanho++;
    lista->Ultimo++;
    return 1;
}

void imprimeLista(ListaProjetos lista)
{
    int Aux;
    for (Aux = lista.Primeiro; Aux <= (lista.Ultimo - 1); Aux++)
    {
        cout << "Chave: " << lista.Item[Aux].chave << endl;
        cout << "Nome: " << lista.Item[Aux].nome << endl;
        cout << "Horas: " << lista.Item[Aux].horas << endl << endl;
    }
    cout << endl;
}

// Retorna em apont o funcionario
int pesquisaItem(ListaProjetos *lista, int chave)
{
    for (int i = lista->Primeiro; i < lista->Ultimo; i++)
    {
        if (chave == lista->Item[i].chave)
        {
            return i; // Retorna posição do item encontrado
        }
    }
    return -1;
}

void retiraItem(TipoApontador p, ListaProjetos *lista)
{
    int Aux;

    if (verificaListaVazia(lista) || p > lista->Ultimo)
    {
        cout << "Erro: Posição não existe na lista\n";
        return;
    }

    p = pesquisaItem(lista, p);

    for (Aux = p; Aux <= lista->Ultimo; Aux++)
    {
        lista->Item[Aux] = lista->Item[Aux + 1];
    }

    lista->Ultimo--;
    lista->tamanho--;
}
