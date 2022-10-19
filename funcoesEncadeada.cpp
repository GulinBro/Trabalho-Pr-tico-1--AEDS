#include <iostream>
#include <windows.h>
#include "listaEncadeada.hpp"

#define MAXTAM 5

using namespace std;

void CriaListaVazia(ListaFuncionario *lista)
{
    if (!listaCriadaEncadeada)
    {
        lista->primeiro = new TipoElemento;
        lista->ultimo = lista->primeiro;
        lista->ultimo->prox = NULL;
        cout << "Lista criada com sucesso!";
        listaCriadaArranjo = true;
    }
    else
    {
        cout << "Lista já existe!";
    }
    Sleep(1500);
}

bool VerificaListaVazia(ListaFuncionario *lista)
{
    return (lista->primeiro == lista->ultimo);
}

int TamanhoLista(ListaFuncionario *lista)
{
    return lista->tamanho;
}

void InsereListaPrimeiro(ListaFuncionario *lista, Funcionario *item)
{
    Apontador aux;
    aux = lista->primeiro->prox;
    lista->primeiro->prox = new TipoElemento;
    lista->primeiro->prox->prox = aux;
    lista->primeiro->prox->item = *item;
    lista->tamanho++;
    AtualizaUltimo(lista);
}

void AtualizaUltimo(ListaFuncionario *lista)
{
    Apontador aux;
    aux = lista->primeiro;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    lista->ultimo = aux;
}

void InsereListaUltimo(ListaFuncionario *lista, Funcionario *item)
{
    lista->ultimo->prox = new TipoElemento;
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->prox = NULL;
    lista->ultimo->item = *item;
    lista->tamanho++;
}

void InsereListaAposElemento(ListaFuncionario *lista, Funcionario *item, int id)
{
    Apontador aux, pAux, x;
    bool find = false;
    pAux = lista->primeiro->prox;
    while (pAux != NULL)
    {
        if (pAux->item.id == id)
        {
            find = true;
            x = pAux;
            aux = x->prox;
            x->prox = new TipoElemento;
            x->prox->prox = aux;
            x->prox->item = *item;
            break;
        }
        pAux = pAux->prox; /* próxima célula */
    }
    if (find)
    {
        cout << "Item inserido com sucesso!";
        AtualizaUltimo(lista);
        lista->tamanho++;
    }
    else
    {
        cout << "Elemento anterior não encontrado na lista.";
    }
}

void ImprimeLista(ListaFuncionario lista)
{
    if (VerificaListaVazia(&lista))
    {
        cout << "Lista vazia!\n";
        Sleep(1000);
        return;
    }
    Apontador aux;
    aux = lista.primeiro->prox;
    while (aux != NULL)
    {
        cout << "ID: " << aux->item.id << endl;
        cout << "Nome: " << aux->item.nome << endl
             << endl;
        aux = aux->prox;
    }
    system("pause");
}

int PesquisaItem(ListaFuncionario *lista, int id, Apontador *encontrado)
{
    Apontador aux;
    aux = lista->primeiro->prox;
    while (aux != NULL)
    {
        if (aux->item.id == id)
        {
            *encontrado = aux;
            return aux->item.id;
        }
        aux = aux->prox;
    }
    return -1;
}

void ImprimeItem(ListaFuncionario *lista, int id)
{
    Apontador aux;
    aux = lista->primeiro->prox;
    while (aux != NULL)
    {
        if (aux->item.id == id)
        {
            cout << "ID: " << aux->item.id << endl;
            cout << "Nome: " << aux->item.nome << endl
                 << endl;
            break;
        }
        aux = aux->prox;
    }
}

void RemoveListaPrimeiro(ListaFuncionario *lista)
{
    if (VerificaListaVazia(lista))
    {
        return;
    }
    Apontador aux;
    aux = lista->primeiro->prox;
    lista->primeiro->prox = aux->prox;
    delete aux;
    lista->tamanho--;
}

void RemoveListaUltimo(ListaFuncionario *lista)
{
    if (VerificaListaVazia(lista))
    {
        return;
    }
    Apontador aux, atual;
    atual = lista->primeiro->prox;
    aux = lista->ultimo;
    while (atual->prox != lista->ultimo)
    {
        atual = atual->prox;
    }
    atual->prox = NULL;
    lista->ultimo = atual;
    delete aux;
    lista->tamanho--;
}

void RemoveItemPorId(ListaFuncionario *lista, int id)
{
    if (VerificaListaVazia(lista))
    {
        return;
    }

    Apontador aux, anterior, x;

    x = lista->primeiro;

    while (x != NULL)
    {
        if (x->prox->item.id == id)
        {
            anterior = x;
            break;
        }
        x = x->prox;
    }
    aux = anterior->prox;
    anterior->prox = aux->prox;
    delete aux;
    lista->tamanho--;
    AtualizaUltimo(lista);
}
