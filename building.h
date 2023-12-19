#include "tree.h"
#include "queue.h"

Tree *func_exception(FILE *arquivo);

Tree* rebuild_huffman_tree (FILE *arquivo);

Tree* build_huffman_tree(int *array);

Tree *build_Tree(priority_queue *pq);

int creating_huffman_string(Tree *huffman, FILE *header);
