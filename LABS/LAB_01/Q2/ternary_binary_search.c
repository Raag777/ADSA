#include <stdio.h>
#include <stdlib.h>

// Global counters for comparisons
int binaryComparisons = 0;
int ternaryComparisons = 0;

// ---------- Binary Search ----------
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        binaryComparisons++;
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

// ---------- Ternary Search ----------
int ternarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        ternaryComparisons++;
        if (arr[mid1] == key) return mid1;

        ternaryComparisons++;
        if (arr[mid2] == key) return mid2;

        if (key < arr[mid1]) {
            high = mid1 - 1;
        } else if (key > arr[mid2]) {
            low = mid2 + 1;
        } else {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }
    return -1;
}

// ---------- MAIN ----------
int main() {
    int n, key;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter %d sorted elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter key to search: ");
    scanf("%d", &key);

    // Reset comparison counters
    binaryComparisons = 0;
    ternaryComparisons = 0;

    // Perform Binary Search
    int bIndex = binarySearch(arr, n, key);

    // Perform Ternary Search
    int tIndex = ternarySearch(arr, 0, n - 1, key);

    // Results
    printf("\n=== Results ===\n");
    if (bIndex != -1)
        printf("Binary Search: Key found at index %d\n", bIndex);
    else
        printf("Binary Search: Key not found\n");

    if (tIndex != -1)
        printf("Ternary Search: Key found at index %d\n", tIndex);
    else
        printf("Ternary Search: Key not found\n");

    printf("\nComparisons made:\n");
    printf("Binary Search comparisons: %d\n", binaryComparisons);
    printf("Ternary Search comparisons: %d\n", ternaryComparisons);

    // ---------- Write data to output.dat ----------
    FILE *fp = fopen("output.dat", "a"); // append mode
    if (fp != NULL) {
        fprintf(fp, "%d %d %d\n", n, binaryComparisons, ternaryComparisons);
        fclose(fp);
        printf("\n Data saved to output.dat\n");
    } else {
        printf("\n Failed to open output.dat for writing\n");
    }

    free(arr);
    return 0;
}
