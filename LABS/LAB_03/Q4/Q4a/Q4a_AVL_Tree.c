#include <stdio.h>
#include <stdlib.h>


// AVL Tree Node

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Height of node
int height(Node* n) {
    return (n == NULL) ? 0 : n->height;
}

// Max of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new node
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}


// Rotations for AVL balancing

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get balance factor
int getBalance(Node* node) {
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}


// INSERT in AVL Tree

Node* insert(Node* node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Find minimum node
Node* minValue(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}


// DELETE in AVL Tree

Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        printf("Key %d does NOT exist in AVL Tree.\n", key);
        return root;
    }

    if (key < root->key) {
        Node* prev = root->left;
        root->left = deleteNode(root->left, key);

        // If nothing changed → key not found
        if (prev == root->left && (prev == NULL || prev->key != key))
            return root;
    }
    else if (key > root->key) {
        Node* prev = root->right;
        root->right = deleteNode(root->right, key);

        if (prev == root->right && (prev == NULL || prev->key != key))
            return root;
    }
    else {
        // KEY FOUND — perform normal AVL deletion
        if (root->left == NULL || root->right == NULL) {
            Node* temp = (root->left) ? root->left : root->right;
            printf("Key %d deleted successfully.\n", key);

            free(root);
            return temp;
        }

        // Two-child case
        Node* temp = minValue(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);

        printf("Key %d deleted successfully.\n", key);
    }

    // If key not found in entire tree
    if (root == NULL)
        return root;

    // Recalculate height
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // BALANCING CASES
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


// Traversals

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

#ifndef TEST_MODE
int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n===== AVL Tree Menu =====\n");
        printf("1. Insert\n2. Delete\n3. Inorder\n4. Preorder\n5. Postorder\n6. Exit\n");
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
                root = deleteNode(root, value);
                break;

            case 3:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;

            case 5:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid!\n");
        }
    }
}
#endif
