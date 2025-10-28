#include <stdio.h>

// Function to find the defective (lighter) coin
int findDefective(int coins[], int n) {
    int low = 0, high = n - 1;

    while (low < high) {
        int mid = low + (high - low) / 2;
        int size = high - low + 1;

        if (size % 2 == 0) {
            int half = size / 2;
            int sumLeft = 0, sumRight = 0;

            for (int i = 0; i < half; i++) {
                sumLeft += coins[low + i];
                sumRight += coins[low + half + i];
            }

            if (sumLeft < sumRight) {
                high = low + half - 1;  // defective in left half
            } else if (sumRight < sumLeft) {
                low = low + half;       // defective in right half
            } else {
                return -1;              // all equal → no defective
            }
        } else {
            // odd number of coins
            int half = size / 2;
            int sumLeft = 0, sumRight = 0;

            for (int i = 0; i < half; i++) {
                sumLeft += coins[low + i];
                sumRight += coins[low + half + 1 + i];
            }

            if (sumLeft < sumRight)
                high = low + half - 1;
            else if (sumRight < sumLeft)
                low = low + half + 1;
            else
                return low + half; // middle one is defective
        }
    }

    // When only one coin remains
    if (low == high)
        return low;

    return -1;  // fallback
}

#ifdef MAIN_PROGRAM
int main() {
    int n;
    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];
    printf("Enter weights of %d coins:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    int index = findDefective(coins, n);

    if (index == -1)
        printf("All coins are perfect. No defective coin found.\n");
    else
        printf("Defective (lighter) coin found at index %d with weight %d\n", index, coins[index]);

    return 0;
}
#endif

