#include <iostream>
#include <fstream>

#include "funcoesArranjo.cpp"
#include "listaArranjo.hpp"
#include "funcoesEncadeada.cpp"
#include "listaEncadeada.hpp"

using namespace std;

void menu()
{
    cout << "--------------------------------------\n";
    cout << "\t\tMenu\n";
    cout << "--------------------------------------\n";
    cout << " 1 - Incluir novo funcionario\n";
    cout << " 2 - Incluir novos projetos\n";
    cout << " 3 - Excluir projetos\n";
    cout << " 4 - Excluir funcionarios sem projeto\n";
    cout << " 5 - Consultar funcionario\n";
    cout << " 6 - Imprimir contra-cheque\n";
    cout << " 7 - Sair\n";
    cout << "Escolha uma opcao: ";
}

// Recupera a lista do arquivo
void recuperaLista(ListaFuncionario *lista)
{
    FILE *file = fopen("funcionarios.bin", "r");
    Funcionario funcionario;
    if (file != NULL)
    {
        // Le a struct de funcionario inteira do arquivo
        while (fread(&funcionario, sizeof(Funcionario), 1, file))
        {
            InsereListaUltimo(lista, &funcionario);
        }
    }
}

// Salva a lista em arquivo
void salvaLista(ListaFuncionario *lista)
{
    FILE *file = fopen("funcionarios.bin", "w");
    Apontador aux = lista->primeiro->prox;
    while (aux != NULL)
    {
        // Salva a struct de funcionario inteira no arquivo
        fwrite(&aux->item, sizeof(Funcionario), 1, file);
        aux = aux->prox;
    }
}

// Passa pela lista inteira apagando os funcionarios
void desalocaLista(ListaFuncionario *lista)
{
    Apontador aux = lista->primeiro->prox;
    Apontador anterior;
    while (aux != NULL)
    {
        anterior = aux;
        aux = aux->prox;
        delete anterior;
    }
    delete aux;
}

int main()
{
    ListaFuncionario lista; // Lista principal de funcionarios
    CriaListaVazia(&lista);
    recuperaLista(&lista);

    int opcao;               // Usado no Swith-Case
    int id;                  // Usado para guardar ids para pesquisa
    Apontador apont;         // Usado como retorno da função PesquisaItem()
    char resposta;           // Usado para guardar as respostas de sim ou nao
    Funcionario funcionario; // Usado no insere funcionario

    cout << "\n";
    do
    {
        menu();
        cin >> opcao;
        switch (opcao)
        {

        // Incluir novo funcionario
        case 1:

            // Verifica se o id do funcionario já existe na lista
            do
            {
                system("cls");
                cout << "Id do funcionario: ";
                cin >> funcionario.id;
            } while (PesquisaItem(&lista, funcionario.id, &apont) != -1);

            cin.ignore();
            cout << "Nome: ";
            cin.getline(funcionario.nome, 50);
            cout << "Endereco: ";
            cin.getline(funcionario.endereco, 50);
            cout << "Numero de dependentes: ";
            cin >> funcionario.dependentes;

            // Cria a lista de projetos do funcionario
            criaListaVazia(&funcionario.projetos);

            cout << "Digite 'S' para incluir projetos nesse funcionarios: ";
            cin >> resposta;
            if (resposta == 's' || resposta == 'S')
            {
                do
                {
                    Projeto projeto;

                    // Verifica se o id do projeto já existe na lista
                    do
                    {
                        system("cls");
                        cout << "Id do projeto: ";
                        cin >> projeto.chave;
                    } while (pesquisaItem(&funcionario.projetos, projeto.chave) != -1);

                    cin.ignore();
                    cout << "Nome do projeto: ";
                    cin.getline(projeto.nome, 50);
                    cout << "Horas Semanais: ";
                    cin >> projeto.horas;

                    insereItem(&funcionario.projetos, projeto);
                    cout << "Digite 'S' para incluir mais um projeto: ";
                    cin >> resposta;
                } while ((resposta == 's' || resposta == 'S') && funcionario.projetos.tamanho < 5);
            }
            InsereListaUltimo(&lista, &funcionario);
            system("cls");
            break;

        // Incluir novos projetos
        case 2:

            system("cls");

            cout << "Digite o id do funcionario: ";
            cin >> id;

            // Retorna em apont o funcionario
            if (PesquisaItem(&lista, id, &apont) != -1)
            {
                cout << "Nome funcionario: " << apont->item.nome << "\n";
                do
                {
                    Projeto projeto;

                    // Verifica se o id do projeto já existe na lista
                    do
                    {
                        system("cls");
                        cout << "Nome do Funcionario: " << apont->item.nome;
                        cout << "\nId do projeto: ";
                        cin >> projeto.chave;
                    } while (pesquisaItem(&apont->item.projetos, projeto.chave) != -1);

                    cout << "Nome do projeto: ";
                    cin >> projeto.nome;
                    cout << "Horas Semanais: ";
                    cin >> projeto.horas;

                    insereItem(&apont->item.projetos, projeto);
                    cout << "Digite 'S' para incluir mais um projeto: ";
                    cin >> resposta;
                } while ((resposta == 's' || resposta == 'S') && apont->item.projetos.tamanho < MAXTAM);
            }
            else
            {
                cout << "Funcionario nao encontrado!\n";
            }
            system("cls");
            break;

        // Excluir projetos
        case 3:

            system("cls");

            cout << "Digite o id do funcionario: ";
            cin >> id;

            // Retorna em apont o funcionario
            if (PesquisaItem(&lista, id, &apont) != -1)
            {
                cout << "Nome do funcionario: " << apont->item.nome;
                cout << "\n\nProjetos\n\n";

                // Imprime a lista de projetos
                imprimeLista(apont->item.projetos);

                cout << "Digite o id do projeto para exclusao: ";
                cin >> id;

                // Verifica se existe um projeto com o id
                if (pesquisaItem(&apont->item.projetos, id) != -1)
                {
                    // Apaga o projeto pelo id
                    retiraItem(id, &apont->item.projetos);
                    cout << "Projeto excluido com sucesso!\n";
                }
                else
                {
                    cout << "Projeto nao encontrado!\n";
                }
            }
            else
            {
                cout << "Funcionario nao encontrado!\n";
            }

            system("pause");
            system("cls");
            break;

        // Excluir funcionarios sem projeto
        case 4:

            system("cls");

            cout << "Excluir funcionarios sem projeto\n";
            cout << " 1 - Excluir um unico funcionario\n";
            cout << " 2 - Excluir todos funcionarios\n";
            cout << "Escolha uma opcao: ";
            cin >> id;

            system("cls");

            if (id == 1)
            {
                cout << "Digite o id do funcionario: ";
                cin >> id;

                // Retorna em apont o funcionario
                if (PesquisaItem(&lista, id, &apont) == -1)
                {
                    cout << "Funcionario nao encontrado!\n";
                }
                else
                {
                    // Apaga o funcinario caso a lista de projetos dele tenha tamanho 0
                    if (apont->item.projetos.tamanho == 0)
                    {
                        RemoveItemPorId(&lista, apont->item.id);
                        cout << "Funcionario excluido\n";
                    }
                    else
                    {
                        cout << "Esse funcionario possui projetos cadastrados\n";
                    }
                }
            }
            else if (id == 2)
            {
                Apontador aux = lista.primeiro->prox;

                // Passa na lista inteira procurando funcionarios com o tamanho da lista de projetos 0
                while (aux != NULL)
                {
                    if (aux->item.projetos.tamanho == 0)
                    {
                        RemoveItemPorId(&lista, aux->item.id);
                    }
                    aux = aux->prox;
                }
                cout << "Funcionarios excluidos\n";
            }

            system("pause");
            system("cls");
            break;

        // Consultar funcionario
        case 5:

            system("cls");
            cout << "Digite o id do funcionario: ";
            cin >> id;

            // Imprime as informações do funcionario caso encontrado
            if (PesquisaItem(&lista, id, &apont) != -1)
            {
                cout << "Id do funcionario: " << apont->item.id;
                cout << "\nNome: " << apont->item.nome;
                cout << "\nEndereco: " << apont->item.endereco;
                cout << "\nDependentes: " << apont->item.dependentes;
                cout << "\n\nProjetos cadastrados\n\n";
                imprimeLista(apont->item.projetos);
            }
            else
            {
                cout << "Funcionario nao encontrado!\n";
            }
            system("pause");
            system("cls");
            break;

        // Imprimir contra-cheque
        case 6:

            system("cls");
            apont = lista.primeiro->prox;
            while (apont != NULL)
            {
                int horasTotais = 0;
                // Conta as horas totais do funcionario
                for (int i = 0; i < apont->item.projetos.tamanho; i++)
                {
                    horasTotais += apont->item.projetos.Item[i].horas;
                }

                float salarioB, salarioL, inss, ir;
                // Salario bruto
                salarioB = horasTotais * 45 + apont->item.dependentes * 35;
                // Desconto do INSS
                inss = salarioB * 0.085;
                // Desconto do imposto
                ir = salarioB * 0.15;
                // Salario Liquido
                salarioL = salarioB - inss - ir;

                cout << "Id: " << apont->item.id;
                cout << "\nNome: " << apont->item.nome;
                cout << "\nHoras Totais: " << horasTotais;
                cout << "\nSalario Bruto: R$ " << salarioB;
                cout << "\nInss: R$ " << inss;
                cout << "\nIr: R$ " << ir;
                cout << "\nSalario Liquido: R$ " << salarioL;
                cout << "\n---------------------------\n";

                apont = apont->prox;
            }
            system("pause");
            system("cls");
            break;
        }

    } while (opcao != 7);

    // So altera o arquivo caso a saída seja pelo menu do programa
    salvaLista(&lista);
    desalocaLista(&lista);

    return 0;
}
