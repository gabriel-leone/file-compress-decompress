#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;

typedef struct _tree Tree;
typedef struct priority_q priority_queue;

struct _tree{
    int frequency;
    BYTE character;
    Tree *next;
    Tree *left;
    Tree *right;
};

Tree* creat_node(BYTE character, int frequencia);

void write_Tree(Tree *root, int *size, FILE *header);

#endif
