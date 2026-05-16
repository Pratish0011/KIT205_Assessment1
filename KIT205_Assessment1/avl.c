#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

static int height(AVLNode* n) {
    if (n == NULL) return 0;
    return n->height;
}

static int int_max(int a, int b) {
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


static AVLNode* rotate_right(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    update_height(y);
    update_height(x);
    return x;
}

static AVLNode* rotate_left(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    update_height(x);
    update_height(y);
    return y;
}

AVLNode* avl_insert(AVLNode* root, const char* key) {
    /* Normal BST insert */
    if (root == NULL) return new_node(key);

    int cmp = strcmp(key, root->key);
    if (cmp < 0)
        root->left = avl_insert(root->left, key);
    else if (cmp > 0)
        root->right = avl_insert(root->right, key);
    else
        return root; /* duplicate, ignore */

    update_height(root);

    /* Rebalance */
    int balance = get_balance(root);

    /* Left Left */
    if (balance > 1 && strcmp(key, root->left->key) < 0)
        return rotate_right(root);

    /* Right Right */
    if (balance < -1 && strcmp(key, root->right->key) > 0)
        return rotate_left(root);

    /* Left Right */
    if (balance > 1 && strcmp(key, root->left->key) > 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    /* Right Left */
    if (balance < -1 && strcmp(key, root->right->key) < 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

void avl_print_inorder(AVLNode* root) {
    if (root == NULL) return;
    avl_print_inorder(root->left);
    printf("    %s\n", root->key);
    avl_print_inorder(root->right);
}

int avl_contains(AVLNode* root, const char* key) {
    if (root == NULL) return 0;
    int cmp = strcmp(key, root->key);
    if (cmp < 0) return avl_contains(root->left, key);
    if (cmp > 0) return avl_contains(root->right, key);
    return 1;
}

void avl_free(AVLNode* root) {
    if (root == NULL) return;
    avl_free(root->left);
    avl_free(root->right);
    free(root);
}
