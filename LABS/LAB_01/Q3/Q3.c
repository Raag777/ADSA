#include <stdio.h>

// Function to find the defective (lighter) coin
int findDefective(int coins[], int n) {
    int low = 0, high = n - 1;

    while (low < high) {
        int mid = low + (high - low) / 2;

        // If the number of coins is even
        if ((high - low + 1) % 2 == 0) {
            int sumLeft = 0, sumRight = 0;
            int leftStart = low;
            int leftEnd = low + (high - low) / 2;
            int rightStart = leftEnd + 1;
            int rightEnd = high;

            for (int i = leftStart; i <= leftEnd; i++) sumLeft += coins[i];
            for (int i = rightStart; i <= rightEnd; i++) sumRight += coins[i];

            if (sumLeft < sumRight) {
                high = leftEnd;
            } else {
                low = rightStart;
            }
        }
        // If the number of coins is odd, exclude the middle coin
        else {
            int leftStart = low;
            int leftEnd = mid - 1;
            int rightStart = mid + 1;
            int rightEnd = high;

            int sumLeft = 0, sumRight = 0;
            for (int i = leftStart; i <= leftEnd; i++) sumLeft += coins[i];
            for (int i = rightStart; i <= rightEnd; i++) sumRight += coins[i];

            if (sumLeft < sumRight) {
                high = leftEnd;
            } else if (sumRight < sumLeft) {
                low = rightStart;
            } else {
                return mid;  // The middle one is defective
            }
        }
    }

    return low;  // Found the defective coin
}


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
        printf("No defective (lighter) coin found. All coins are perfect.\n");
    else
        printf("Defective (lighter) coin found at index %d with weight %d\n", index, coins[index]);

    return 0;
}
