#ifndef PROTO1_H
#define PROTO1_H

#include "avl.h"

#define TABLE_SIZE 100

typedef struct P1Node {
    char id[20];
    AVLNode* relations;
    struct P1Node* next;
} P1Node;

typedef struct {
    P1Node* buckets[TABLE_SIZE];
} P1Table;

P1Table* p1_create();

#endif
