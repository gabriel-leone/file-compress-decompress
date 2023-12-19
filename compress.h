#ifndef COMPRESS_H
#define COMPRESS_H

#define MAX_TABLE_SIZE 150
#define MAX_FREQUENCY_SIZE 256
#define MAX_FILENAME_SIZE 200

#include "building.h"

void frequency_count(FILE *arquivo, int *array);

BYTE add_bit(BYTE c_saida, short int pos);

void creat_table(BYTE tabela[][MAX_TABLE_SIZE], Tree *bt, BYTE *string, int position);

void compress(char *nome_do_arquivo);

void write_compress(BYTE tabela[][MAX_TABLE_SIZE], FILE *arquivo, FILE *saida, int tree_size);

#endif