#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct ListNode {
    char key[20];
    struct ListNode* next;
} ListNode;

ListNode* list_insert(ListNode* head, const char* key);
void list_print(ListNode* head);
void list_free(ListNode* head);
int list_contains(ListNode* head, const char* key);

#endif
