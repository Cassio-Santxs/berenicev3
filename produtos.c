#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "headers.h"

void menuDeProdutos( cadastro_produtos **ptrProdutos,
                     int *tamanhoVetorProdts, int * contadorProdutos)
{

    int flag = 1, codigo;
    int i = 0;
    char voltar = 'q';

    while(flag == 1)
    {
        while(codigo != 7)
        {
            system("cls");

            printf("\n\n=====\t\t||\t\t MENU DE PRODUTOS \t\t||\t\t=====\n\n");

            printf("\n \t C�digo  \t Op��o              \t\n");
            printf("\n \t 1       \t Exibir             \t");
            printf("\n \t 2       \t Cadastrar          \t");
            printf("\n \t 3       \t Atualizar          \t");
            printf("\n \t 4       \t Excluir            \t");
            printf("\n \t 5       \t Salvar             \t");
            printf("\n \t 6       \t Ler                \t");
            printf("\n \t 7       \t Voltar             \t\n");

            printf("\nDigite o c�digo para selecionar a op��o: ");
            scanf("%d", &codigo);
            getchar();

            switch(codigo)
            {
            case 1:
                flag = 0;

                system("cls");

                if(*contadorProdutos > 0)
                {
                    exibirProdutos(*ptrProdutos,
                                   *tamanhoVetorProdts);
                }
                else
                {
                    printf("\n\aAVISO: Voc� n�o possui produtos cadastrados.\n");
                }

                break;

            case 2:
                flag = 0;

                system("cls");

                int addProdutos = 0;

                printf("\n\n=====\t\t||\t\t CADASTRO DE PRODUTOS \t\t||\t\t=====\n\n");
                printf("\nDigite a quantidade de produtos que voc� quer cadastrar: ");
                scanf("%i", &addProdutos);
                getchar();


                if(*contadorProdutos == 0)
                {
                    *tamanhoVetorProdts = addProdutos;
                    *ptrProdutos = (cadastro_produtos*) calloc(addProdutos,sizeof(cadastro_produtos));
                }
                else if((*contadorProdutos)+addProdutos > *tamanhoVetorProdts)
                {
                    int novoTamVetor = *contadorProdutos + addProdutos;

                    // Aloca a nova �rea de mem�ria para os produtos
                    cadastro_produtos *aux = (cadastro_produtos*) realloc(*ptrProdutos, novoTamVetor*sizeof(cadastro_produtos));

                    if(aux == NULL)
                    {
                        printf("ERRO");
                        exit(1);
                    }

                    memset(aux+*tamanhoVetorProdts, 0, (novoTamVetor-(*tamanhoVetorProdts))*sizeof(cadastro_produtos));

                    // Atualiza os ponteiros para a nova �rea
                    *ptrProdutos = aux;

                    *tamanhoVetorProdts = novoTamVetor;
                }

                if(*ptrProdutos == NULL)
                {
                    printf("\aERRO");
                    exit(1);
                }

                for(i=0; i < addProdutos; i++)
                {
                    cadastrarProdutos(*ptrProdutos,
                                      *tamanhoVetorProdts);
                }
                *contadorProdutos += addProdutos;

                break;

            case 3:
                flag = 0;

                system("cls");

                if(*contadorProdutos > 0)
                {
                    exibirProdutos(*ptrProdutos,
                                   *tamanhoVetorProdts);

                    atualizarProduto(*ptrProdutos, *tamanhoVetorProdts);
                }
                else
                {
                    printf("\n\aAVISO: Voc� n�o possui produtos cadastrados.\n");
                }

                break;

            case 4:
                flag = 0;

                system("cls");

                if(*contadorProdutos > 0)
                {
                    exibirProdutos(*ptrProdutos,
                                   *tamanhoVetorProdts);

                    if(excluirProduto(*ptrProdutos,
                                   *tamanhoVetorProdts) == 1)
                    {
                        *contadorProdutos = *contadorProdutos - 1;
                    }
                }
                else
                {
                    printf("\n\aAVISO: Voc� n�o possui produtos cadastrados.\n");
                }

                break;

            case 5:
                flag = 0;

                if(*contadorProdutos > 0)
                {
                    salvarProdutos(*ptrProdutos, *tamanhoVetorProdts, *contadorProdutos);
                    printf("\nArquivo salvo com sucesso!");
                }
                else
                {
                    printf("\n\aAVISO: Voc� n�o possui produtos cadastrados.\n");
                }

                break;

            case 6:
                flag = 0;

                lerProdutos(*ptrProdutos, *tamanhoVetorProdts, *contadorProdutos);
                printf("\nArquivo lido com sucesso!");

                break;

            case 7:
                flag = 0;

                printf("\nVoc� ser� redirecinado ao menu principal. Aperte qualquer tecla para continuar.");
                scanf("%c", &voltar);

                system("cls");

                break;

            default:
                flag = 1;
                printf("\n\aC�digo inv�lido!");
                scanf("%c", &voltar);

                system("cls");

                break;
            }

            if(codigo != 7)
            {
                printf("\n\nVoc� ser� redirecinado ao menu de produtos. Aperte qualquer tecla para continuar.");
                scanf("%c", &voltar);
            }
        }
    }
}

void exibirProdutos(cadastro_produtos *ptrProdutos,
                    int tamanhoVetorProdts)
{

    char voltar;

    printf("\n\n=====\t\t||\t\t PRODUTOS \t\t||\t\t=====\n\n");
    printf("\n\t ID      \t Produto \t Pre�o        \t Estoque \t\n");

    for(int i = 0; i<tamanhoVetorProdts; i++)
    {
        if(ptrProdutos[i]. id > 0)
        {
            printf("\n\t %ld   \t\t %s      \t R$ %.2f      \t %i      \t",
                   ptrProdutos[i].id,
                   ptrProdutos[i].nome,
                   ptrProdutos[i].preco,
                   ptrProdutos[i].estoque);
        }
    }
}

void cadastrarProdutos(cadastro_produtos *ptrProdutos,
                       int tamanhoVetorProdts)
{

    int i;
    int flag = 0;

    for(i = 0; i < tamanhoVetorProdts; i++)
    {
        int ptr = -1;
        float preco = -1;
        long int id = -1;
        flag = 0;

        if(ptrProdutos[i].id == 0)
        {

            while (flag == 0)
            {
                printf("\nDigite o ID do produto sendo este maior que 0: ");
                scanf("%li",&id);

                if(id < 1)
                {
                    flag = 0;
                    printf("\nC�digo inv�lido");
                }
                else if(procuraProduto(ptrProdutos, tamanhoVetorProdts, id) != -1)
                {
                    flag = 0;
                    printf("\nC�digo ja existente!\n");
                }
                else
                {
                    flag = 1;
                    ptrProdutos[i].id = id;
                }
            }

            getchar();
            printf("\nDigite o nome do produto de ID %li com at� 25 caracteres: ", ptrProdutos[i].id);
            fgets(ptrProdutos[i].nome,25,stdin);
            char lenp1 = strlen(ptrProdutos[i].nome);
            if(ptrProdutos[i].nome[lenp1 -1]=='\n')
            {
                ptrProdutos[i].nome [--lenp1] = 0;
            }
            else
            {
                int ch;
                do ch = getchar();
                while (ch != '\n'); // limpa caracteres extra
            }

            do
            {
                printf("\nDigite o estoque do produto de ID %li sendo este valor maior ou igual a 0: ", ptrProdutos[i].id);
                scanf("%i", &ptrProdutos[i].estoque);
                getchar();

                if(ptrProdutos[i].estoque < 0)
                {
                    printf("Quantidade inv�lida!");
                }

            }
            while(ptrProdutos[i].estoque < 0);

            do
            {
                printf("\nDigite o pre�o do produto de ID %li sendo este valor maior ou igual a 0: ", ptrProdutos[i].id);
                scanf("%f", &ptrProdutos[i].preco);
                getchar();

                if(ptrProdutos[i].preco < 0)
                {
                    printf("Quantidade inv�lida!");
                }
            }
            while(ptrProdutos[i].preco < 0);
        }
    }
}

void atualizarProduto(cadastro_produtos *ptrProdutos,
                      int tamanhoVetorProdts)
{
    printf("\n\n=====\t\t||\t\t ATUALIZA��O DE PRODUTOS \t\t||\t\t=====\n\n");
    long int idDigitado = 0;

    int flag = 0,
        quantidadeAntiga,
        quantidadeNova = -1,
        indice;

    float valorAntigo,
          valorNovo = -1;

    char voltar;



    do
    {
        printf("\nDigite o ID do produto que voc� que alterar: ");
        scanf("%li", &idDigitado);
        getchar();

        indice = procuraProduto(ptrProdutos, tamanhoVetorProdts, idDigitado);

        flag = 1;

        if(indice == -1)
        {
            flag = 0;
            printf("\nProduto n�o encontrado!");
        }
    }
    while(flag == 0);


    quantidadeAntiga = ptrProdutos[indice].estoque;
    valorAntigo = ptrProdutos[indice].preco;



    do
    {
        printf("\nDigite o novo estoque do produto de ID %li sendo este valor maior ou igual a 0: ", ptrProdutos[indice].id);
        scanf("%i", &ptrProdutos[indice].estoque);
        getchar();

        if(ptrProdutos[indice].estoque < 0)
        {
            printf("Quantidade inv�lida!");
        }
    }
    while(ptrProdutos[indice].estoque < 0);

    do
    {
        printf("\nDigite o novo pre�o do produto de ID %li sendo este valor maior ou igual a 0: ", ptrProdutos[indice].id);
        scanf("%f", &ptrProdutos[indice].preco);
        getchar();

        if(ptrProdutos[indice].preco < 0)
        {
            printf("Quantidade inv�lida!");
        }
    }
    while(ptrProdutos[indice].preco < 0);

    system("cls");

    printf("\n\n=====\t\t||\t\t         ANTIGO          \t\t||\t\t=====\n\n");

    printf("\n\t ID     \t Produto \t Pre�o     \t Quantidade \t\n");
    printf("\n\t %d     \t %s      \t R$ %.2f   \t %d         \t", ptrProdutos[indice].id, ptrProdutos[indice].nome, valorAntigo, quantidadeAntiga);

    printf("\n\n=====\t\t||\t\t          NOVO           \t\t||\t\t=====\n\n");
    printf("\n\t %d     \t %s      \t R$ %.2f   \t %d         \t", ptrProdutos[indice].id, ptrProdutos[indice].nome, ptrProdutos[indice].preco, ptrProdutos[indice].estoque);
}

int excluirProduto(cadastro_produtos *ptrProdutos,
                    int *tamanhoVetorProdts)
{

    long int idDigitado = 0;

    int flag = 0,
        indice,
        confirma,
        retorno = 0;

    char voltar;


    printf("\n\n=====\t\t||\t\t EXCLUIR PRODUTOS \t\t||\t\t=====\n\n");

    do
    {
        printf("\nDigite o ID do produto que voc� que excluir: ");
        scanf("%li", &idDigitado);
        getchar();

        indice = procuraProduto(ptrProdutos, tamanhoVetorProdts, idDigitado);

        flag = 1;

        if(indice == -1)
        {
            flag = 0;
            printf("\nProduto n�o encontrado!");
        }
    }
    while(flag == 0);

    printf("\n\n=====\t\t||\t\t CONFIRMAR EXCLUS�O \t\t||\t\t=====\n\n");
    printf("\n\t %d     \t %s      \t R$ %.2f   \t %d         \t", ptrProdutos[indice].id, ptrProdutos[indice].nome, ptrProdutos[indice].preco, ptrProdutos[indice].estoque);

    while(flag == 1)
    {
        printf("\n\nAperte 1 para confirmar e 2 para cancelar: ");
        scanf("%i", &confirma);
        getchar();

        switch(confirma)
        {
        case 1:
            flag = 0;
            ptrProdutos[indice].id = 0;
            printf("\nProduto excluido com sucesso.");
            retorno = 1;

            break;

        case 2:
            flag = 0;
            printf("\nA��o cancelada.");
            retorno = 0;

            break;

        default:
            flag = 1;

            printf("\nC�digo inv�lido!");

            break;
        }
    }

    return retorno;
}

int procuraProduto(cadastro_produtos *ptrProdutos,
                   int tamanhoVetorProdts, long int idDigitado)
{

    int i = 0;
    int retorno = 0;

    for(i = 0; i<tamanhoVetorProdts; i++)
    {

        if (ptrProdutos[i].id == idDigitado)
        {
            if(ptrProdutos[i]. id == 0)
            {
                retorno = -1;
            }
            else
            {
                retorno = i;
            }

            break;
        }
        else
        {
            retorno = -1;
        }
    }

    return retorno;
}

void salvarProdutos(cadastro_produtos *ptrProdutos,
                    int tamanhoVetorProdts,
                    int contadorProdutos)
{
    int i = 0;

    FILE *arquivo = fopen("produtos.txt","w");
    if(arquivo == NULL)
    {
        printf("\nERRO NA ABERTURA DO ARQUIVO\n");
        exit(2);
    }
    printf("TESTE");
    fprintf(arquivo, "\nTamanhoVetorProdts: %d", tamanhoVetorProdts);
    fprintf(arquivo, "\nContadorProdutos: %d", contadorProdutos);
    printf("TESTE");

    for(i = 0; i < tamanhoVetorProdts; i++)
    {
        fprintf(arquivo, "\nID: %ld", ptrProdutos[i].id);
        fprintf(arquivo, "\nProduto: %s", ptrProdutos[i].nome);
        fprintf(arquivo, "\nEstoque: %d", ptrProdutos[i].estoque);
        fprintf(arquivo, "\nValor: %.2f", ptrProdutos[i].preco);
    }
    printf("TESTE");
    fclose(arquivo);
}

void lerProdutos(cadastro_produtos *ptrProdutos,
                 int *tamanhoVetorProdts,
                 int *contadorProdutos)
{
    int i = 0;

    FILE *arquivo = fopen("produtos.txt","r");

    if(arquivo == NULL)
    {
        printf("ERRO NA ABERTURA DO ARQUIVO");
        exit(2);
    }

    for(i = 0; i < tamanhoVetorProdts; i++) //usado para printar
    {
        fscanf(arquivo, "%d %d %ld %s %d %.2f", tamanhoVetorProdts, contadorProdutos, ptrProdutos[i].id, ptrProdutos[i].nome, ptrProdutos[i].estoque, ptrProdutos[i].preco);
    }

    fclose(arquivo);

}
