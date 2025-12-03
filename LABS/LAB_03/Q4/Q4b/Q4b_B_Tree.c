#include <stdio.h>
#include <stdlib.h>

#define T 3   // Minimum degree


// B–Tree Node

typedef struct BTreeNode {
    int keys[2*T - 1];
    struct BTreeNode* child[2*T];
    int n;
    int leaf;
} BTreeNode;

// Create node
BTreeNode* createNode(int leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2*T; i++)
        node->child[i] = NULL;
    return node;
}


// Traversal

void traverse(BTreeNode* root) {
    if (!root) return;

    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->child[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->child[i]);
}


// Search

BTreeNode* search(BTreeNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;

    if (i < root->n && root->keys[i] == k)
        return root;

    if (root->leaf)
        return NULL;

    return search(root->child[i], k);
}


// Split child node

void splitChild(BTreeNode* parent, int i, BTreeNode* fullChild) {
    BTreeNode* newChild = createNode(fullChild->leaf);
    newChild->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        newChild->keys[j] = fullChild->keys[j + T];

    if (!fullChild->leaf) {
        for (int j = 0; j < T; j++)
            newChild->child[j] = fullChild->child[j + T];
    }

    fullChild->n = T - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->child[j + 1] = parent->child[j];

    parent->child[i + 1] = newChild;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = fullChild->keys[T - 1];
    parent->n++;
}


// Insert non-full

void insertNonFull(BTreeNode* root, int k) {
    int i = root->n - 1;

    if (root->leaf) {
        while (i >= 0 && k < root->keys[i]) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        root->keys[i + 1] = k;
        root->n++;
    }
    else {
        while (i >= 0 && k < root->keys[i])
            i--;

        if (root->child[i + 1]->n == 2*T - 1) {
            splitChild(root, i + 1, root->child[i + 1]);
            if (k > root->keys[i + 1])
                i++;
        }
        insertNonFull(root->child[i + 1], k);
    }
}


// Insert key

BTreeNode* insert(BTreeNode* root, int k) {
    // Case 1: Empty tree → create root
    if (root == NULL) {
        root = createNode(1);  // leaf
        root->keys[0] = k;
        root->n = 1;
        return root;
    }

    // Case 2: Root is full → split before inserting
    if (root->n == 2*T - 1) {
        BTreeNode* s = createNode(0); // new non-leaf root
        s->child[0] = root;
        splitChild(s, 0, root);
        insertNonFull(s, k);
        return s;
    }

    // Case 3: Normal insert
    insertNonFull(root, k);
    return root;
}



// Delete (leaf delete + key-not-found message)

BTreeNode* deleteKey(BTreeNode* root, int k) {
    if (!root) {
        printf("Tree is empty.\n");
        return root;
    }

    int i = 0;

    // Find first key >= k
    while (i < root->n && k > root->keys[i])
        i++;

    
    // Case 1: Key FOUND in node
    
    if (i < root->n && root->keys[i] == k) {

        // Leaf delete
        if (root->leaf) {
            for (int j = i; j < root->n - 1; j++)
                root->keys[j] = root->keys[j + 1];

            root->n--;
            printf("Key %d deleted successfully.\n", k);
            return root;
        }

        // Internal delete not supported
        printf("Key %d found but NOT a leaf. Internal delete not implemented.\n", k);
        return root;
    }

    
    // Case 2: Key NOT FOUND
    
    if (root->leaf) {
        printf("Key %d does NOT exist in B-Tree.\n", k);
        return root;
    }

    // Go deeper into correct subtree
    root->child[i] = deleteKey(root->child[i], k);
    return root;
}

#ifndef TEST_MODE

// Main Menu for B-tree

int main() {
    BTreeNode* root = NULL;
    int choice, value;

    while (1) {
        printf("\n===== B-Tree Menu =====\n");
        printf("1. Insert\n2. Delete (Leaf only)\n3. Traverse\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                root = deleteKey(root, value);
                break;

            case 3:
                printf("B-Tree Traversal: ");
                traverse(root);
                printf("\n");
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid!\n");
        }
    }
}
#endif
