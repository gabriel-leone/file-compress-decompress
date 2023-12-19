#include "compress.h"

// Função para contar a frequência de cada caractere no arquivo
void frequency_count(FILE *arquivo, int *array)
{

    BYTE character;

    // Lê cada caractere do arquivo até o final
    while ((fscanf(arquivo, "%c", &character)) != EOF)
    {
        ++array[character]; // Incrementa a contagem para o caractere lido
    }

    return;
}

// Função para adicionar um bit à posição especificada em um byte
BYTE add_bit(BYTE c_saida, short int pos)
{
    // Retorna o byte com o bit adicionado na posição especificada
    return (c_saida | (1 << (7 - pos)));
}

// Função para escrever o arquivo comprimido
void write_compress(BYTE tabela[][MAX_TABLE_SIZE], FILE *arquivo, FILE *saida, int tree_size)
{

    BYTE aux, character = 0, cond = 1;
    short int size = 0, position = 0;

    // Lê cada caractere do arquivo até o final
    while ((fscanf(arquivo, "%c", &aux)) != EOF)
    {
        position = 0;

        // Percorre a tabela de compressão para o caractere lido
        while (tabela[aux][position] != '\0')
        {
            // Se o tamanho é 8, escreve o caractere no arquivo de saída e reinicia o caractere e o tamanho
            if (size == 8)
            {
                fprintf(saida, "%c", character);
                size = 0;
                character = 0;
            }
            // Se o bit na posição atual é 1, adiciona o bit ao caractere
            if (tabela[aux][position] & 1)
                character = add_bit(character, size);
            // Incrementa o tamanho e a posição
            ++size;
            ++position;
        }
    }

    // Calcula o número de bits de lixo no último byte
    BYTE lixo = (8 - size) << 5;
    fprintf(saida, "%c", character);

    // Posiciona o ponteiro do arquivo no início
    fseek(saida, 0, SEEK_SET);
    // Combina os bits de lixo com os 3 bits mais significativos do tamanho da árvore
    lixo = lixo | tree_size >> 8;
    // Escreve o primeiro byte no arquivo de saída
    fprintf(saida, "%c", lixo);
    // Obtém os 8 bits menos significativos do tamanho da árvore
    lixo = tree_size & 255;
    // Escreve o segundo byte no arquivo de saída
    fprintf(saida, "%c", lixo);

    return;
}

// Função para criar a tabela de compressão
void creat_table(BYTE tabela[][MAX_TABLE_SIZE], Tree *bt, BYTE *string, int position)
{

    // Verifica se o nó atual é uma folha (não tem filhos)
    if (bt->left == NULL && bt->right == NULL)
    {
        string[position] = '\0';                              // Termina a string com um caractere nulo
        strncpy(tabela[bt->character], string, position + 1); // Copia a string para a tabela de compressão na posição do caractere do nó
        return;
    }
    if (bt->left != NULL)
    {
        // Se o nó atual tem um filho à esquerda, adiciona '0' à string
        string[position] = '0';
        // Chama a função recursivamente para o filho à esquerda
        creat_table(tabela, bt->left, string, position + 1);
    }
    if (bt->right != NULL)
    {
        // Se o nó atual tem um filho à direita, adiciona '1' à string
        string[position] = '1';
        // Chama a função recursivamente para o filho à direita
        creat_table(tabela, bt->right, string, position + 1);
    }
}

// Função para comprimir o arquivo
void compress(char *nome_entrada)
{

    char nome_saida[MAX_FILENAME_SIZE], aux[MAX_TABLE_SIZE];
    int frequency[MAX_FREQUENCY_SIZE];
    memset(frequency, 0, sizeof(frequency)); // Inicializa o array de frequência com zeros

    FILE *arquivo;
    FILE *novo_arquivo;

    // Loop infinito para tentar abrir o arquivo de entrada
    while (1)
    {
        system("cls");                       // Limpa a tela do terminal
        arquivo = fopen(nome_entrada, "rb"); // Tenta abrir o arquivo de entrada no modo de leitura binária
        if (arquivo == NULL)
        {
            printf("O nome do arquivo ou caminho esta incorreto!\n Tente novamente...");
            system("pause");
            continue;
        }
        break;
    }

    strcpy(nome_saida, nome_entrada);
    strcat(nome_saida, ".comp");

    frequency_count(arquivo, frequency);
    fseek(arquivo, 0, SEEK_SET); // Reposiciona o ponteiro do arquivo de entrada para o início

    // Cria a árvore de Huffman a partir do array de frequências
    Tree *bt = build_huffman_tree(frequency);

    // Cria um array bidimensional para armazenar a tabela de compressão
    BYTE tabela[256][150];
    creat_table(tabela, bt, aux, 0);

    system("cls");

    // Tenta abrir o novo arquivo no modo de escrita binária
    novo_arquivo = fopen(nome_saida, "wb");

    int size_tree;
    BYTE aux1;
    // Chama a função para criar a string de Huffman e armazena o tamanho da árvore
    size_tree = creating_huffman_string(bt, novo_arquivo);

    // Chama a função para escrever o arquivo comprimido
    write_compress(tabela, arquivo, novo_arquivo, size_tree);

    printf("Concluido com exito!\n\n");

    fclose(arquivo);
    fclose(novo_arquivo);
}