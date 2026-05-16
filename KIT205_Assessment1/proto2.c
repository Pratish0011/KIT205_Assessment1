#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proto2.h"

static int hash(const char* key) {
    int h = 0;
    while (*key) {
        h = (h * 31 + *key) % TABLE_SIZE;
        key++;
    }
    return h;
}

P2Table* p2_create() {
    P2Table* t = (P2Table*)calloc(1, sizeof(P2Table));
    return t;
}

static P2Node* p2_find_or_create(P2Table* t, const char* id) {
    int idx = hash(id);
    P2Node* curr = t->buckets[idx];

    while (curr != NULL) {
        if (strcmp(curr->id, id) == 0) return curr;
        curr = curr->next;
    }

    P2Node* n = (P2Node*)malloc(sizeof(P2Node));
    strncpy(n->id, id, 19);
    n->id[19] = '\0';
    n->relations = NULL;
    n->next = t->buckets[idx];
    t->buckets[idx] = n;
    return n;
}

void p2_add_relation(P2Table* authors, P2Table* papers,
    const char* author_id, const char* paper_id) {
    P2Node* author = p2_find_or_create(authors, author_id);
    P2Node* paper = p2_find_or_create(papers, paper_id);
    author->relations = list_insert(author->relations, paper_id);
    paper->relations = list_insert(paper->relations, author_id);
}