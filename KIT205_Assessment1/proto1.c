#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proto1.h"

static int hash(const char* key) {
    int h = 0;
    while (*key) {
        h = (h * 31 + *key) % TABLE_SIZE;
        key++;
    }
    return h;
}

P1Table* p1_create() {
    P1Table* t = (P1Table*)calloc(1, sizeof(P1Table));
    return t;
}

static P1Node* p1_find_or_create(P1Table* t, const char* id) {
    int idx = hash(id);
    P1Node* curr = t->buckets[idx];

    while (curr != NULL) {
        if (strcmp(curr->id, id) == 0) return curr;
        curr = curr->next;
    }

    P1Node* n = (P1Node*)malloc(sizeof(P1Node));
    strncpy(n->id, id, 19);
    n->id[19] = '\0';
    n->relations = NULL;
    n->next = t->buckets[idx];
    t->buckets[idx] = n;
    return n;
}