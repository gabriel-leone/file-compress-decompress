#ifndef QUEUE_H
#define  QUEUE_H

#include "tree.h"

typedef struct priority_q priority_queue;

struct priority_q{
    Tree *head;
};

priority_queue* creat_priority_queue();

void enqueue(Tree *node, priority_queue *pq);

Tree* dequeue(priority_queue *pq);

#endif