#include "decompress.h"

// Função para escrever o arquivo descomprimido
void write_decompress(Tree *bt, FILE *entrada, FILE *saida, int lixo)
{
    // Define um ponteiro auxiliar para a árvore de Huffman
    Tree *aux = bt;
    // Define variáveis para armazenar os caracteres lidos do arquivo e um auxiliar
    BYTE character, aux1;
    int i;

    // Lê o primeiro caractere do arquivo de entrada
    fscanf(entrada, "%c", &character);
    aux1 = character;

    // Lê cada caractere do arquivo de entrada até o final
    while (fscanf(entrada, "%c", &character) != EOF)
    {
        // Loop para cada bit do caractere
        for (i = 7; i >= 0; i--)
        {
            // Se o nó atual é uma folha (não tem filhos)
            if (aux->left == NULL && aux->right == NULL)
            {
                // Escreve o caractere do nó no arquivo de saída
                fprintf(saida, "%c", aux->character);
                // Reinicia o ponteiro auxiliar para o início da árvore
                aux = bt;
            }
            // Se o bit na posição atual é 1, move o ponteiro auxiliar para a direita
            if (aux1 & 1 << i)
                aux = aux->right;
            // Se o bit na posição atual é 0, move o ponteiro auxiliar para a esquerda
            else
                aux = aux->left;
        }
        aux1 = character;
    }

    // Loop para os bits restantes no último byte
    for (i = 7; lixo <= 8; lixo++, i--)
    {
        // Se o nó atual é uma folha (não tem filhos)
        if (aux->left == NULL && aux->right == NULL)
        {
            fprintf(saida, "%c", aux->character);
            aux = bt;
        }
        // Se o bit na posição atual é 1, move o ponteiro auxiliar para a direita
        if (aux1 & 1 << i)
            aux = aux->right;
        // Se o bit na posição atual é 0, move o ponteiro auxiliar para a esquerda
        else
            aux = aux->left;
    }
    return;
}

// Função para verificar se o nome do arquivo termina com ".comp"
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

// Função para descomprimir o arquivo
void decompress(char *nome_entrada)
{

    char nome_saida[200];

    FILE *arquivo_entrada;
    FILE *arquivo_saida;

    BYTE character;
    int lixo, size_tree = 0, i;
    Tree *bt = NULL;

    // Loop infinito para tentar abrir o arquivo de entrada
    while (1)
    {
        system("cls");
        // Tenta abrir o arquivo de entrada no modo de leitura binária
        arquivo_entrada = fopen(nome_entrada, "rb");

        if (arquivo_entrada == NULL)
        {
            printf("O nome do arquivo ou caminho esta incorreto!\n Tente novamente...");
            system("pause");
            continue;
        }
        // Se a verificação do nome do arquivo passar (ou seja, o arquivo tem a extensão ".comp")
        if (verification(nome_entrada))
            continue;
        break;
    }

    // Copia o nome do arquivo de entrada para o nome do arquivo de saída, excluindo a extensão ".comp"
    strncpy(nome_saida, nome_entrada, strlen(nome_entrada) - 5);
    nome_saida[strlen(nome_entrada) - 5] = '\0';
    

    // Lê o primeiro caractere do arquivo de entrada
    fscanf(arquivo_entrada, "%c", &character);
    // Extrai os 3 bits mais significativos, que representam o tamanho do lixo
    lixo = character >> 5;

    // Extrai os 5 bits menos significativos do primeiro caractere, que representam a parte alta do tamanho da árvore
    size_tree = character & 0b00011111;
    // Desloca os bits para a esquerda para fazer espaço para a parte baixa do tamanho da árvore
    size_tree = size_tree << 8;
    // Lê o próximo caractere do arquivo de entrada
    fscanf(arquivo_entrada, "%c", &character);
    // Combina a parte baixa do tamanho da árvore com a parte alta
    size_tree = size_tree | character;

    system("cls");

    // Se o tamanho da árvore é 2, chama a função de exceção para reconstruir a árvore de Huffman
    if (size_tree == 2)
        bt = (Tree *)func_exception(arquivo_entrada);
    // Se o tamanho da árvore não é 2, chama a função normal para reconstruir a árvore de Huffman
    else
        bt = rebuild_huffman_tree(arquivo_entrada);

    arquivo_saida = fopen(nome_saida, "wb");

    if (arquivo_saida == NULL)
    {
        printf("Erro ao abrir o arquivo de saída!\n");
        return;
    }

    // Chama a função para escrever o arquivo descomprimido
    write_decompress(bt, arquivo_entrada, arquivo_saida, lixo);

    printf(" Concluido com exito\n");

    fclose(arquivo_saida);
    fclose(arquivo_entrada);

    return;
}
