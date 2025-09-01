#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list (to handle collisions)
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Sorted insertion in linked list (for bucket elements)
void sortedInsert(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL || (*head)->data >= data) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL && temp->next->data < data)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// Address Calculation Sort function
void addressCalculationSort(int arr[], int n) {
    // Number of buckets
    int bucketCount = n;

    // Create buckets
    struct Node* buckets[bucketCount];
    for (int i = 0; i < bucketCount; i++)
        buckets[i] = NULL;

    // Simple hash function: (value % n)
    for (int i = 0; i < n; i++) {
        int index = arr[i] % bucketCount;
        sortedInsert(&buckets[index], arr[i]);
    }

    // Collect elements back into array
    int idx = 0;
    for (int i = 0; i < bucketCount; i++) {
        struct Node* temp = buckets[i];
        while (temp != NULL) {
            arr[idx++] = temp->data;
            struct Node* del = temp;
            temp = temp->next;
            free(del);
        }
    }
}

// Function to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {23, 45, 12, 8, 34, 56, 10, 2, 19};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    addressCalculationSort(arr, n);

    printf("Sorted array:   ");
    printArray(arr, n);

    return 0;
}