#include <stdio.h>

// Iterative function to find defective coin
int findDefective(int coins[], int n) {
    int low = 0, high = n-1;

    while (low < high) {
        int mid = low + (high - low) / 2;
        
        if(coins[low] < coins[high]){
            return low;
        }
       
        if(coins[mid] < coins[low]){
            return mid;
        }
         
        // Calculate weights of left and right halves
        int sumLeft = 0, sumRight = 0;
        for (int i = low; i <= mid; i++) sumLeft += coins[i];
        for (int i = mid+1; i <= high; i++) sumRight += coins[i];
        
        
        
        if (sumLeft < sumRight) {
            high = mid;         // defective coin is in left half
        } else if (sumRight < sumLeft) {
            low = mid + 1;      // defective coin is in right half
        } else {
            return -1;           // no defective coin
        }
        
        if(coins[mid] == coins[low] ){
            return mid;
        }
    }

    return low;  // found defective coin index
    
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