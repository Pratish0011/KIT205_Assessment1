#ifndef PROTO2_H
#define PROTO2_H

#include "linkedlist.h"

#define TABLE_SIZE 100

typedef struct P2Node {
    char id[20];
    ListNode* relations;
    struct P2Node* next;
} P2Node;

typedef struct {
    P2Node* buckets[TABLE_SIZE];
} P2Table;

P2Table* p2_create();

#endif
