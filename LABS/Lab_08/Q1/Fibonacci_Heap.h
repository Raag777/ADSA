#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

typedef struct FibNode {
    int id;
    int key;
    int degree;
    int mark;
    struct FibNode *parent, *child, *left, *right;
} FibNode;

typedef struct FibHeap {
    FibNode *min;
    int n;
} FibHeap;

FibHeap* createFibHeap();
FibNode* createNode(int key);
void fibHeapInsert(FibHeap *H, FibNode *x);
FibNode* fibHeapExtractMin(FibHeap *H);
void fibHeapDecreaseKey(FibHeap *H, FibNode *x, int newKey);
void fibHeapDelete(FibHeap *H, FibNode *x);
FibNode* findNodeById(FibHeap *H, int id);
void freeHeap(FibHeap *H);

#endif
