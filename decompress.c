#include "decompress.h"

void write_decompress(Tree *bt, FILE *entrada, FILE *saida, int lixo)
{
    Tree *aux = bt;
    BYTE character, aux1;
    int i;

    fscanf(entrada, "%c", &character);
    aux1 = character;

    while (fscanf(entrada, "%c", &character) != EOF)
    {

        for (i = 7; i >= 0; i--)
        {

            if (aux->left == NULL && aux->right == NULL)
            {
                fprintf(saida, "%c", aux->character);
                aux = bt;
            }

            if (aux1 & 1 << i)
                aux = aux->right;
            else
                aux = aux->left;
        }
        aux1 = character;
    }

    for (i = 7; lixo <= 8; lixo++, i--)
    {
        if (aux->left == NULL && aux->right == NULL)
        {
            fprintf(saida, "%c", aux->character);
            aux = bt;
        }
        if (aux1 & 1 << i)
            aux = aux->right;
        else
            aux = aux->left;
    }
    return;
}

int verification(char *nome)
{
    int condition = 0, i, j, size = strlen(nome);
    char *comp;
    comp = ".comp";

    for (i = size - 1, j = 4; i > size - 6; i--, j--)
        if (comp[j] != nome[i])
            condition = 1;

    if (condition)
    {
        printf("Nao se trata de um arquivo compactado.\nArquivos compactados devem ter a extensao: .comp\n");
        system("pause");
    }
    return condition;
}

void decompress(char *nome_entrada)
{

    char nome_saida[200];

    FILE *arquivo_entrada;
    FILE *arquivo_saida;

    BYTE character;
    int lixo, size_tree = 0, i;
    Tree *bt = NULL;

    while (1)
    {

        system("cls");
        arquivo_entrada = fopen(nome_entrada, "rb");

        if (arquivo_entrada == NULL)
        {
            printf("O nome do arquivo ou caminho esta incorreto!\n Tente novamente...");
            system("pause");
            continue;
        }
        if (verification(nome_entrada))
            continue;
        break;
    }

    strncpy(nome_saida, nome_entrada, strlen(nome_entrada) - 5);

    system("cls");
    printf("Aguarde ...\n");

    // LENDO O TAMANHO DO LIXO
    fscanf(arquivo_entrada, "%c", &character);
    lixo = character >> 5;

    // LENDO O TAMANHO DA ARVORE
    size_tree = character & 0b00011111;
    size_tree = size_tree << 8;
    fscanf(arquivo_entrada, "%c", &character);
    size_tree = size_tree | character;

    system("cls");
    printf("Aguarde ...\n");

    if (size_tree == 2)
        bt = (Tree *)func_exception(arquivo_entrada);
    else
        bt = rebuild_huffman_tree(arquivo_entrada);
    arquivo_saida = fopen(nome_saida, "wb");

    write_decompress(bt, arquivo_entrada, arquivo_saida, lixo);

    printf(" Concluido com exito\n");

    fclose(arquivo_saida);
    fclose(arquivo_entrada);

    return;
}
