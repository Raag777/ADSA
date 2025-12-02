#include <stdio.h>

// ---------------------------------------------
// MEDIAN OF THREE
// ---------------------------------------------
int medianOfThree(int arr[], int low, int mid, int high) {
    if (arr[low] > arr[mid]) {
        int t = arr[low]; arr[low] = arr[mid]; arr[mid] = t;
    }
    if (arr[low] > arr[high]) {
        int t = arr[low]; arr[low] = arr[high]; arr[high] = t;
    }
    if (arr[mid] > arr[high]) {
        int t = arr[mid]; arr[mid] = arr[high]; arr[high] = t;
    }
    return mid;
}

int partitionMedian(int arr[], int low, int high) {
    int mid = (low + high) / 2;
    int median = medianOfThree(arr, low, mid, high);

    int t = arr[median];
    arr[median] = arr[high];
    arr[high] = t;

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    int temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;

    return i + 1;
}

void quickSortMedian(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionMedian(arr, low, high);
        quickSortMedian(arr, low, pi - 1);
        quickSortMedian(arr, pi + 1, high);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

#ifndef TEST_MODE
int main() {
    int n;
    printf("Enter array size: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    quickSortMedian(arr, 0, n - 1);

    printf("\nSorted using Quick Sort (Median-of-Three): ");
    printArray(arr, n);

    return 0;
}
#endif
