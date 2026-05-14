#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

ListNode* list_insert(ListNode* head, const char* key) {
    /* Check for duplicate at head */
    if (head != NULL && strcmp(key, head->key) == 0)
        return head;

    /* Insert before head if smaller */
    if (head == NULL || strcmp(key, head->key) < 0) {
        ListNode* n = (ListNode*)malloc(sizeof(ListNode));
        strncpy(n->key, key, 19);
        n->key[19] = '\0';
        n->next = head;
        return n;
    }