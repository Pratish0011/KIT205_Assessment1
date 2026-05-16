#include <stdio.h>
#include <string.h>
#include "test.h"
#include "avl.h"
#include "linkedlist.h"
#include "proto1.h"

static int passed = 0;
static int failed = 0;

static void check(const char* desc, int condition) {
    if (condition) {
        printf("  PASS: %s\n", desc);
        passed++;
    }
    else {
        printf("  FAIL: %s\n", desc);
        failed++;
    }
}

static void test_avl() {
    printf("\n[AVL Tree Tests]\n");

    AVLNode* root = NULL;
    root = avl_insert(root, "P003");
    root = avl_insert(root, "P001");
    root = avl_insert(root, "P002");
    root = avl_insert(root, "P001");

    check("AVL contains P001", avl_contains(root, "P001"));
    check("AVL contains P002", avl_contains(root, "P002"));
    check("AVL contains P003", avl_contains(root, "P003"));
    check("AVL does not contain P999", !avl_contains(root, "P999"));
    check("AVL tree is balanced (height <= 2)", root->height <= 2);

    avl_free(root);
    check("AVL free (no crash)", 1);
}

static void test_list() {
    printf("\n[Linked List Tests]\n");

    ListNode* head = NULL;
    head = list_insert(head, "P003");
    head = list_insert(head, "P001");
    head = list_insert(head, "P002");
    head = list_insert(head, "P001");

    check("List contains P001", list_contains(head, "P001"));
    check("List contains P003", list_contains(head, "P003"));
    check("List does not contain P999", !list_contains(head, "P999"));
    check("List head is P001 (sorted)", strcmp(head->key, "P001") == 0);
    check("List second is P002 (sorted)", strcmp(head->next->key, "P002") == 0);

    list_free(head);
    check("List free (no crash)", 1);
}

static void test_proto1() {
    printf("\n[Prototype 1 - Hash Table of AVL Trees]\n");

    P1Table* authors = p1_create();
    P1Table* papers = p1_create();

    p1_add_relation(authors, papers, "A001", "P001");
    p1_add_relation(authors, papers, "A001", "P003");
    p1_add_relation(authors, papers, "A001", "P002");
    p1_add_relation(authors, papers, "A002", "P001");

    P1Node* found_author = NULL;
    for (int i = 0; i < TABLE_SIZE; i++) {
        P1Node* curr = authors->buckets[i];
        while (curr != NULL) {
            if (strcmp(curr->id, "A001") == 0) found_author = curr;
            curr = curr->next;
        }
    }

    check("A001 exists in authors table", found_author != NULL);
    if (found_author != NULL) {
        check("A001 has P001", avl_contains(found_author->relations, "P001"));
        check("A001 has P002", avl_contains(found_author->relations, "P002"));
        check("A001 has P003", avl_contains(found_author->relations, "P003"));
    }

    P1Node* found_paper = NULL;
    for (int i = 0; i < TABLE_SIZE; i++) {
        P1Node* curr = papers->buckets[i];
        while (curr != NULL) {
            if (strcmp(curr->id, "P001") == 0) found_paper = curr;
            curr = curr->next;
        }
    }
    check("P001 exists in papers table", found_paper != NULL);
    if (found_paper != NULL) {
        check("P001 has A001", avl_contains(found_paper->relations, "A001"));
        check("P001 has A002", avl_contains(found_paper->relations, "A002"));
    }

    printf("  Papers by A001 (expect P001 P002 P003):\n");
    p1_print_relations(authors, "A001");
    printf("  Authors of P001 (expect A001 A002):\n");
    p1_print_relations(papers, "P001");

    p1_free(authors);
    p1_free(papers);
    check("Proto1 free (no crash)", 1);
}

void run_all_tests() {
    printf("=============================\n");
    printf("       UNIT TESTS\n");
    printf("=============================\n");

    passed = 0;
    failed = 0;

    test_avl();
    test_list();
    test_proto1();

    printf("\n=============================\n");
    printf("  %d passed, %d failed\n", passed, failed);
    printf("=============================\n\n");
}