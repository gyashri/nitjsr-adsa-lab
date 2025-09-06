#include <stdio.h>

// Function to swap two numbers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Radix Exchange Sort (bitwise quick sort)
void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0)
        return;

    int i = left, j = right;

    // Partition based on current bit
    while (i <= j) {
        // Move i forward if bit is 0
        while (i <= j && ((arr[i] >> bit) & 1) == 0)
            i++;

        // Move j backward if bit is 1
        while (i <= j && ((arr[j] >> bit) & 1) == 1)
            j--;

        // Swap misplaced elements
        if (i < j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }

    // Recursively sort the partitions on the next lower bit
    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, i, right, bit - 1);
}

// Utility function to find the maximum bit position
int getMaxBit(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int bit = 0;
    while (max > 0) {
        bit++;
        max >>= 1;
    }
    return bit - 1; // return index of MSB
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {23, 5, 98, 12, 45, 67, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    int maxBit = getMaxBit(arr, n);
    radixExchangeSort(arr, 0, n - 1, maxBit);

    printf("Sorted array:   ");
    printArray(arr, n);

    return 0;
}
