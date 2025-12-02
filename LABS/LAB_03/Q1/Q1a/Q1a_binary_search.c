#include <stdio.h>

// ---------------------------------------------
// NON-RECURSIVE BINARY SEARCH
// ---------------------------------------------
int binarySearchIterative(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// ---------------------------------------------
// RECURSIVE BINARY SEARCH
// ---------------------------------------------
int binarySearchRecursive(int arr[], int low, int high, int key) {
    if (low > high)
        return -1;

    int mid = (low + high) / 2;

    if (arr[mid] == key)
        return mid;
    else if (arr[mid] < key)
        return binarySearchRecursive(arr, mid + 1, high, key);
    else
        return binarySearchRecursive(arr, low, mid - 1, key);
}

#ifndef TEST_MODE
int main() {
    int n, key;

    printf("Enter no. of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter sorted elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter key to search: ");
    scanf("%d", &key);

    int r1 = binarySearchIterative(arr, n, key);
    int r2 = binarySearchRecursive(arr, 0, n - 1, key);

    printf("\nIterative Binary Search Index: %d\n", r1);
    printf("Recursive Binary Search Index: %d\n", r2);

    return 0;
}
#endif