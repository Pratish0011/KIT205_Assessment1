#ifndef AVL_H
#define AVL_H

typedef struct AVLNode {
    char key[20];
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

AVLNode* avl_insert(AVLNode* root, const char* key);
void avl_print_inorder(AVLNode* root);
void avl_free(AVLNode* root);
int avl_contains(AVLNode* root, const char* key);

#endif