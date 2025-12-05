#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node* insert(Node* root, int key);
Node* deleteKey(Node* root, int key);
Node* search(Node* root, int key);
void inorder(Node* root);
void preorder(Node* root);

#endif
