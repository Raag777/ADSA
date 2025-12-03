#include <stdio.h>
#include <stdlib.h>


// Structure for BST Node

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;


// Create a new node

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


// Insert a node in BST

Node* insert(Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}


// Find minimum node (used in delete)

Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}


// Delete a node from BST

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);

    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}


// Inorder Traversal (LNR)
// Sorted order

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}


// Preorder Traversal (NLR)

void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}


// Postorder Traversal (LRN)

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}


// SAFE INPUT FUNCTION (Prevents infinite invalid input)

int safeInput(int *value) {
    char buffer[50];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return 0;

    // Validate: ensure input is a valid integer
    char *end;
    long num = strtol(buffer, &end, 10);

    // If end does not reach newline → invalid input
    if (end == buffer || *end != '\n')
        return 0;

    *value = (int)num;
    return 1;
}


#ifndef TEST_MODE
int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n===== Binary Search Tree Operations =====\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Inorder Traversal\n");
        printf("4. Preorder Traversal\n");
        printf("5. Postorder Traversal\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (!safeInput(&choice)) {
            printf("Invalid input! Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                if (!safeInput(&value)) {
                    printf("Invalid input! Not inserted.\n");
                    continue;
                }
                root = insert(root, value);
                printf("Inserted successfully!\n");
                break;

            case 2:
                printf("Enter value to delete: ");
                if (!safeInput(&value)) {
                    printf("Invalid input! No deletion.\n");
                    continue;
                }
                root = deleteNode(root, value);
                printf("Deleted successfully (if existed).\n");
                break;

            case 3:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 5:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;

            case 6:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice! Enter a number between 1–6.\n");
        }
    }

    return 0;
}
#endif
