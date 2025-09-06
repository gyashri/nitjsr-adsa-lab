#include <stdio.h>
#include <stdlib.h>

// Function to find maximum value in the array
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// Insertion sort for sorting individual buckets
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Function to implement Bucket Sort
void bucketSort(int arr[], int n) {
    int max = getMax(arr, n);
    int bucketCount = n;  // number of buckets = size of array

    // Create buckets
    int *buckets[bucketCount];
    int bucketSizes[bucketCount];
    int bucketCapacity[bucketCount];

    for (int i = 0; i < bucketCount; i++) {
        bucketSizes[i] = 0;
        bucketCapacity[i] = 5;  // initial capacity
        buckets[i] = (int *)malloc(bucketCapacity[i] * sizeof(int));
    }

    // Distribute array elements into buckets
    for (int i = 0; i < n; i++) {
        int index = (arr[i] * bucketCount) / (max + 1);  // bucket index
        if (bucketSizes[index] == bucketCapacity[index]) {
            bucketCapacity[index] *= 2;
            buckets[index] = (int *)realloc(buckets[index], bucketCapacity[index] * sizeof(int));
        }
        buckets[index][bucketSizes[index]++] = arr[i];
    }

    // Sort individual buckets and concatenate
    int idx = 0;
    for (int i = 0; i < bucketCount; i++) {
        if (bucketSizes[i] > 0) {
            insertionSort(buckets[i], bucketSizes[i]);
            for (int j = 0; j < bucketSizes[i]; j++)
                arr[idx++] = buckets[i][j];
        }
        free(buckets[i]); // free memory
    }
}

// Function to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {42, 32, 33, 52, 37, 47, 51};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    bucketSort(arr, n);

    printf("Sorted array:   ");
    printArray(arr, n);

    return 0;
}
