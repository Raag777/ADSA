#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_DEGREE 64    // safe upper bound for degrees for typical lab sizes


//  Fibonacci Heap Node

typedef struct FibNode {
    int id;                     // unique id for user reference
    int key;
    int degree;
    int mark;
    struct FibNode *parent;
    struct FibNode *child;
    struct FibNode *left;
    struct FibNode *right;
} FibNode;


//  Fibonacci Heap Structure

typedef struct FibHeap {
    FibNode *min;
    int n;
} FibHeap;

// Global id counter for nodes
static int GLOBAL_NODE_ID = 1;


//  Create Heap & Node

FibHeap* createFibHeap() {
    FibHeap *H = (FibHeap*) malloc(sizeof(FibHeap));
    if (!H) { fprintf(stderr, "Memory allocation failed\n"); exit(1); }
    H->min = NULL;
    H->n = 0;
    return H;
}

FibNode* createNode(int key) {
    FibNode *node = (FibNode*) malloc(sizeof(FibNode));
    if (!node) { fprintf(stderr, "Memory allocation failed\n"); exit(1); }
    node->id = GLOBAL_NODE_ID++;
    node->key = key;
    node->degree = 0;
    node->mark = 0;
    node->parent = node->child = NULL;
    node->left = node->right = node;
    return node;
}


//  Insert Operation

void fibHeapInsert(FibHeap *H, FibNode *x) {
    if (H->min == NULL) {
        H->min = x;
    } else {
        // insert x into root list just after min
        x->right = H->min->right;
        x->left = H->min;
        H->min->right->left = x;
        H->min->right = x;
        if (x->key < H->min->key)
            H->min = x;
    }
    H->n++;
}


//  Helper: Link two roots (make y child of x)

void fibHeapLink(FibHeap *H, FibNode *y, FibNode *x) {
    // remove y from root list
    y->left->right = y->right;
    y->right->left = y->left;

    // make y a child of x
    y->parent = x;
    if (x->child == NULL) {
        x->child = y;
        y->left = y->right = y;
    } else {
        y->right = x->child->right;
        y->left = x->child;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->mark = 0;
}


//  Consolidate — merge trees of equal degree

void consolidate(FibHeap *H) {
    if (H->min == NULL) return;

    FibNode *A[MAX_DEGREE];
    for (int i = 0; i < MAX_DEGREE; ++i) A[i] = NULL;

    // collect root list nodes to an array to iterate safely
    FibNode *start = H->min;
    FibNode *w = start;
    FibNode *nodes[1024];   // temporary array to store root list snapshot
    int cnt = 0;
    do {
        nodes[cnt++] = w;
        w = w->right;
        if (cnt >= 1024) break; // safety cap for extremely large root lists
    } while (w != start);

    for (int i = 0; i < cnt; ++i) {
        FibNode *x = nodes[i];
        int d = x->degree;
        while (d < MAX_DEGREE && A[d] != NULL) {
            FibNode *y = A[d];
            if (x->key > y->key) {
                FibNode *tmp = x; x = y; y = tmp;
            }
            fibHeapLink(H, y, x);
            A[d] = NULL;
            d++;
        }
        if (d < MAX_DEGREE) A[d] = x;
    }

    // rebuild root list and find new min
    H->min = NULL;
    for (int i = 0; i < MAX_DEGREE; ++i) {
        if (A[i] != NULL) {
            if (H->min == NULL) {
                H->min = A[i];
                A[i]->left = A[i]->right = A[i];
            } else {
                // insert A[i] into root list (after H->min)
                A[i]->right = H->min->right;
                A[i]->left = H->min;
                H->min->right->left = A[i];
                H->min->right = A[i];
                if (A[i]->key < H->min->key)
                    H->min = A[i];
            }
        }
    }
}


//  Extract-Min

FibNode* fibHeapExtractMin(FibHeap *H) {
    FibNode *z = H->min;
    if (z == NULL) return NULL;

    // move each child of z to root list
    if (z->child != NULL) {
        FibNode *child = z->child;
        // collect children to avoid infinite loops while moving
        FibNode *start = child;
        FibNode *curnode = start;
        FibNode *childrenArr[1024];
        int ccount = 0;
        do {
            childrenArr[ccount++] = curnode;
            curnode = curnode->right;
            if (ccount >= 1024) break;
        } while (curnode != start);

        for (int i = 0; i < ccount; ++i) {
            FibNode *c = childrenArr[i];
            // detach parent pointer
            c->parent = NULL;
            // insert into root list (after current min)
            c->left = H->min;
            c->right = H->min->right;
            H->min->right->left = c;
            H->min->right = c;
        }
        z->child = NULL;
    }

    // remove z from root list
    z->left->right = z->right;
    z->right->left = z->left;

    if (z == z->right) {
        H->min = NULL;
    } else {
        H->min = z->right;
        consolidate(H);
    }

    H->n--;
    // return z (caller should print info and free it)
    return z;
}


//  Cut Operation

void cut(FibHeap *H, FibNode *x, FibNode *y) {
    // remove x from child list of y
    if (x->right == x) {
        // x was the only child
        y->child = NULL;
    } else {
        x->right->left = x->left;
        x->left->right = x->right;
        if (y->child == x)
            y->child = x->right;
    }
    y->degree--;

    // add x to root list after H->min
    x->left = H->min;
    x->right = H->min->right;
    H->min->right->left = x;
    H->min->right = x;

    x->parent = NULL;
    x->mark = 0;
}


//  Cascading Cut

void cascadingCut(FibHeap *H, FibNode *y) {
    FibNode *z = y->parent;
    if (z != NULL) {
        if (y->mark == 0) {
            y->mark = 1;
        } else {
            cut(H, y, z);
            cascadingCut(H, z);
        }
    }
}


//  Decrease Key

void fibHeapDecreaseKey(FibHeap *H, FibNode *x, int newKey) {
    if (x == NULL) return;
    if (newKey > x->key) {
        printf("Error: new key is larger than current key.\n");
        return;
    }
    x->key = newKey;
    FibNode *y = x->parent;
    if (y != NULL && x->key < y->key) {
        if (H->min == NULL) {
            // should not happen but safe-guard
            x->parent = NULL;
            x->mark = 0;
        } else {
            cut(H, x, y);
            cascadingCut(H, y);
        }
    }
    if (H->min == NULL || x->key < H->min->key)
        H->min = x;
}


//  Delete Node (by node pointer)

void fibHeapDelete(FibHeap *H, FibNode *x) {
    if (x == NULL) return;
    fibHeapDecreaseKey(H, x, INT_MIN);
    FibNode *removed = fibHeapExtractMin(H);
    if (removed) {
        // free memory
        free(removed);
    }
}


//  Utility: Print root list (shows id:key pairs)

void printRootList(FibHeap *H) {
    if (H->min == NULL) {
        printf("Heap is empty.\n");
        return;
    }
    FibNode *start = H->min;
    FibNode *cur = start;
    printf("Root List: ");
    do {
        printf("(%d:%d) ", cur->id, cur->key);
        cur = cur->right;
    } while (cur != start);
    printf("\n");
}


//  Find a node by id (full heap traversal). Returns ptr or NULL
//  Safe recursive traversal using visited flag via temporary mark set.

FibNode* findNodeByIdRecursive(FibNode *root, int id) {
    if (root == NULL) return NULL;

    // Use an explicit stack/fixed array approach to avoid recursion depth problems:
    FibNode *stack[4096];
    int top = 0;
    FibNode *start = root;
    FibNode *cur = start;
    // push entire circular list starting at root
    do {
        stack[top++] = cur;
        cur = cur->right;
        if (top >= 4096) break;
    } while (cur != start);

    while (top > 0) {
        FibNode *node = stack[--top];
        if (node->id == id) return node;
        if (node->child != NULL) {
            FibNode *cstart = node->child;
            FibNode *c = cstart;
            do {
                stack[top++] = c;
                c = c->right;
                if (top >= 4096) break;
            } while (c != cstart);
        }
    }
    return NULL;
}

FibNode* findNodeById(FibHeap *H, int id) {
    if (H == NULL || H->min == NULL) return NULL;
    return findNodeByIdRecursive(H->min, id);
}


//  Free whole heap (helper for clean exit) - frees all nodes

void freeSubtree(FibNode *root) {
    if (root == NULL) return;
    // iterate root-level circular list snapshot
    FibNode *nodes[4096];
    int cnt = 0;
    FibNode *cur = root;
    do {
        nodes[cnt++] = cur;
        cur = cur->right;
        if (cnt >= 4096) break;
    } while (cur != root);

    for (int i = 0; i < cnt; ++i) {
        FibNode *n = nodes[i];
        if (n->child) freeSubtree(n->child);
        free(n);
    }
}

void freeHeap(FibHeap *H) {
    if (H == NULL) return;
    if (H->min != NULL) freeSubtree(H->min);
    free(H);
}

#ifndef TEST_MODE

int main() {
    FibHeap *H = createFibHeap();
    int choice;
    while (1) {
        printf("\n===== Fibonacci Heap Menu =====\n");
        printf("1. Insert Key\n");
        printf("2. Extract Min\n");
        printf("3. Decrease Key (by node id)\n");
        printf("4. Delete Node (by node id)\n");
        printf("5. Print Root List\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            // clear invalid input
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (choice == 1) {
            int key;
            printf("Enter key to insert: ");
            if (scanf("%d", &key) != 1) { int c; while ((c = getchar()) != '\n' && c != EOF) {} printf("Invalid key.\n"); continue; }
            FibNode *n = createNode(key);
            fibHeapInsert(H, n);
            printf("Inserted node id=%d key=%d\n", n->id, n->key);
        } else if (choice == 2) {
            FibNode *min = fibHeapExtractMin(H);
            if (min) {
                printf("Extracted Min -> id=%d key=%d\n", min->id, min->key);
                free(min);
            } else {
                printf("Heap is empty.\n");
            }
        } else if (choice == 3) {
            int id, newKey;
            printf("Enter node id to decrease: ");
            if (scanf("%d", &id) != 1) { int c; while ((c = getchar()) != '\n' && c != EOF) {} printf("Invalid id.\n"); continue; }
            FibNode *node = findNodeById(H, id);
            if (!node) {
                printf("Node with id=%d not found.\n", id);
                continue;
            }
            printf("Current key of id=%d is %d. Enter new smaller key: ", id, node->key);
            if (scanf("%d", &newKey) != 1) { int c; while ((c = getchar()) != '\n' && c != EOF) {} printf("Invalid key.\n"); continue; }
            fibHeapDecreaseKey(H, node, newKey);
            printf("Decreased node id=%d to key=%d\n", id, node->key);
        } else if (choice == 4) {
            int id;
            printf("Enter node id to delete: ");
            if (scanf("%d", &id) != 1) { int c; while ((c = getchar()) != '\n' && c != EOF) {} printf("Invalid id.\n"); continue; }
            FibNode *node = findNodeById(H, id);
            if (!node) {
                printf("Node with id=%d not found.\n", id);
                continue;
            }
            fibHeapDelete(H, node);
            printf("Deleted node id=%d\n", id);
        } else if (choice == 5) {
            printRootList(H);
        } else if (choice == 6) {
            // cleanup and exit
            freeHeap(H);
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
#endif
