#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

static int height(AVLNode* n) {
    if (n == NULL) return 0;
    return n->height;
}

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static AVLNode* new_node(const char* key) {
    AVLNode* n = (AVLNode*)malloc(sizeof(AVLNode));
    strncpy(n->key, key, 19);
    n->key[19] = '\0';
    n->height = 1;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void update_height(AVLNode* n) {
    n->height = 1 + max(height(n->left), height(n->right));
}

static int get_balance(AVLNode* n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

