#define _CRT_SECURE_NO_WARNINGS
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

    /* Walk the list to find insertion point */
    ListNode* curr = head;
    while (curr->next != NULL) {
        int cmp = strcmp(key, curr->next->key);
        if (cmp == 0) return head; 
        if (cmp < 0) {
            ListNode* n = (ListNode*)malloc(sizeof(ListNode));
            strncpy(n->key, key, 19);
            n->key[19] = '\0';
            n->next = curr->next;
            curr->next = n;
            return head;
        }
        curr = curr->next;
    }

    /* Append at end */
    ListNode* n = (ListNode*)malloc(sizeof(ListNode));
    strncpy(n->key, key, 19);
    n->key[19] = '\0';
    n->next = NULL;
    curr->next = n;
    return head;
}

void list_print(ListNode* head) {
    ListNode* curr = head;
    while (curr != NULL) {
        printf("    %s\n", curr->key);
        curr = curr->next;
    }
}

int list_contains(ListNode* head, const char* key) {
    ListNode* curr = head;
    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) return 1;
        curr = curr->next;
    }
    return 0;
}

void list_free(ListNode* head) {
    while (head != NULL) {
        ListNode* tmp = head;
        head = head->next;
        free(tmp);
    }
}