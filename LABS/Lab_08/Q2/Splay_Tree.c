#include <stdio.h>
#include <stdlib.h>

//  SPLAY TREE NODE 
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Utility Function – Create New Node
Node* newNode(int key) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

//  RIGHT ROTATION 
Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

//  LEFT ROTATION 
Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

//  SPLAY OPERATION 
Node* splay(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    // ---- Key in left subtree ----
    if (key < root->key) {
        if (root->left == NULL)
            return root;

        // Zig-Zig (LL case)
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        // Zig-Zag (LR case)
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        return (root->left == NULL) ? root : rightRotate(root);
    }

    // ---- Key in right subtree ----
    else {
        if (root->right == NULL)
            return root;

        // Zag-Zig (RL case)
        if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        // Zag-Zag (RR case)
        else if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        return (root->right == NULL) ? root : leftRotate(root);
    }
}

//  INSERT 
Node* insert(Node* root, int key) {
    if (root == NULL)
        return newNode(key);

    // Splay last searched node
    root = splay(root, key);

    // Key already exists
    if (root->key == key)
        return root;

    Node* n = newNode(key);

    if (key < root->key) {
        n->right = root;
        n->left = root->left;
        root->left = NULL;
    } else {
        n->left = root;
        n->right = root->right;
        root->right = NULL;
    }

    return n;
}

//  DELETE 
Node* deleteKey(Node* root, int key) {
    Node* temp;
    if (!root) return NULL;

    root = splay(root, key);

    if (root->key != key)
        return root;  // key not found

    // If left subtree is NULL, replace by right subtree
    if (!root->left) {
        temp = root;
        root = root->right;
    } else {
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }

    free(temp);
    return root;
}

//  SEARCH 
Node* search(Node* root, int key) {
    return splay(root, key);
}

//  TRAVERSALS 
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

#ifndef TEST_MODE

int main() {
    Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\n===== SPLAY TREE MENU =====\n");
        printf("1. Insert\n2. Search\n3. Delete\n4. Inorder Traversal\n5. Preorder Traversal\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                printf("Inserted!\n");
                break;

            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                root = search(root, key);
                printf("Tree splayed with %d at root (or nearest accessed node).\n", key);
                break;

            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deleteKey(root, key);
                printf("Deleted if existed.\n");
                break;

            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }
}
#endif
