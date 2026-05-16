#include <stdio.h>
#include <string.h>
#include "test.h"
#include "avl.h"
#include "linkedlist.h"

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
    root = avl_insert(root, "P001"); /* duplicate */

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
    head = list_insert(head, "P001"); /* duplicate */

    check("List contains P001", list_contains(head, "P001"));
    check("List contains P003", list_contains(head, "P003"));
    check("List does not contain P999", !list_contains(head, "P999"));
    check("List head is P001 (sorted)", strcmp(head->key, "P001") == 0);
    check("List second is P002 (sorted)", strcmp(head->next->key, "P002") == 0);

    list_free(head);
    check("List free (no crash)", 1);
}

void run_all_tests() {
    printf("=============================\n");
    printf("       UNIT TESTS\n");
    printf("=============================\n");

    passed = 0;
    failed = 0;

    test_avl();
    test_list();

    printf("\n=============================\n");
    printf("  %d passed, %d failed\n", passed, failed);
    printf("=============================\n\n");
}