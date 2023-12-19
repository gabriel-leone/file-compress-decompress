#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include "building.h"

void write_decompress(Tree *bt, FILE *entrada, FILE *saida, int lixo);

int verification(char *nome);

void decompress(char *nome_entrada);

#endif
