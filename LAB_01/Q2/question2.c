#include <stdio.h>

// Global counters for comparisons
int binaryComparisons = 0;
int ternaryComparisons = 0;

// Binary Search function
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

// Ternary Search function
int ternarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        // two midpoints
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        ternaryComparisons++;
        if (arr[mid1] == key) return mid1;
        
        ternaryComparisons++;
        if (arr[mid2] == key) return mid2;

        if (key < arr[mid1]) {
            high = mid1 - 1;
        }
        else if (key > arr[mid2]) {
            low = mid2 + 1;
        }
        else {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }
    return -1;
}

int main() {
    int n, key;

    // Input array
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d sorted elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Input key
    printf("Enter key to search: ");
    scanf("%d", &key);

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

    return 0;
}
