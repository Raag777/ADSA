#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256
#define MAX_CODE_LEN 100

// Node structure for Huffman tree
typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

// Create a new node
Node* newNode(char ch, int freq) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->ch = ch;
    n->freq = freq;
    n->left = n->right = NULL;
    return n;
}

// Min-heap for Huffman tree
typedef struct {
    int size;
    Node* arr[MAX_CHARS];
} MinHeap;

// Swap nodes
void swap(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

// Heapify
void heapify(MinHeap* heap, int i) {
    int smallest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < heap->size && heap->arr[l]->freq < heap->arr[smallest]->freq)
        smallest = l;

    if (r < heap->size && heap->arr[r]->freq < heap->arr[smallest]->freq)
        smallest = r;

    if (smallest != i) {
        swap(&heap->arr[i], &heap->arr[smallest]);
        heapify(heap, smallest);
    }
}

// Extract minimum node
Node* extractMin(MinHeap* heap) {
    Node* temp = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
    return temp;
}

// Insert node into heap
void insertHeap(MinHeap* heap, Node* node) {
    int i = heap->size++;
    while (i > 0 && node->freq < heap->arr[(i-1)/2]->freq) {
        heap->arr[i] = heap->arr[(i-1)/2];
        i = (i-1)/2;
    }
    heap->arr[i] = node;
}

// Build Huffman Tree
Node* buildHuffman(int freq[]) {
    MinHeap heap;
    heap.size = 0;

    for (int i = 0; i < MAX_CHARS; i++)
        if (freq[i] > 0)
            insertHeap(&heap, newNode(i, freq[i]));

    while (heap.size > 1) {
        Node* left = extractMin(&heap);
        Node* right = extractMin(&heap);

        Node* combined = newNode('\0', left->freq + right->freq);
        combined->left = left;
        combined->right = right;

        insertHeap(&heap, combined);
    }

    return extractMin(&heap);
}

// Generate Huffman Codes
void generateCodes(Node* root, char code[], int depth,
                   char codes[MAX_CHARS][MAX_CODE_LEN]) {
    if (!root)
        return;

        // Leaf node
    if (!root->left && !root->right) {

        // Special case: Only one character in entire file
        if (depth == 0) {
            code[0] = '0';
            code[1] = '\0';
        } else {
            code[depth] = '\0';
        }

        strcpy(codes[(unsigned char)root->ch], code);
        return;
    }


    code[depth] = '0';
    generateCodes(root->left, code, depth + 1, codes);

    code[depth] = '1';
    generateCodes(root->right, code, depth + 1, codes);
}

#ifndef TEST_MODE

int main() {
    char filename[100];
    printf("Enter input text file name: ");
    scanf("%s", filename);

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening input file.\n");
        return 1;
    }

    int freq[MAX_CHARS] = {0};
    char text[10000];
    int idx = 0;

    // Read file and count frequencies
    char c;
    while ((c = fgetc(fp)) != EOF) {
        text[idx++] = c;
        freq[(unsigned char)c]++;
    }
    text[idx] = '\0';
    fclose(fp);

    // Build Huffman Tree
    Node* root = buildHuffman(freq);

    // Generate codes
    char codes[MAX_CHARS][MAX_CODE_LEN] = {{0}};
    char tempCode[MAX_CODE_LEN];
    generateCodes(root, tempCode, 0, codes);

    
    // WRITE HUFFMAN CODES TO FILE
    
    FILE* codeFile = fopen("codes.txt", "w");
    if (!codeFile) {
        printf("Error creating codes.txt\n");
        return 1;
    }

    fprintf(codeFile, "Huffman Codes:\n");
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            fprintf(codeFile, "'%c' -> %s\n", i, codes[i]);
        }
    }
    fclose(codeFile);

    
    // WRITE ENCODED OUTPUT TO FILE
    
    FILE* outFile = fopen("encoded_output.txt", "w");
    if (!outFile) {
        printf("Error creating encoded_output.txt\n");
        return 1;
    }

    for (int i = 0; i < idx; i++)
        fprintf(outFile, "%s", codes[(unsigned char)text[i]]);

    fclose(outFile);

    // Display message
    printf("\nEncoding complete!\n");
    printf("Huffman codes saved in: codes.txt\n");
    printf("Encoded bitstream saved in: encoded_output.txt\n");

    return 0;
}
#endif
