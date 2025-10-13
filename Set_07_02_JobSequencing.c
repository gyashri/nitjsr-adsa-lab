#include <stdio.h>
#include <stdlib.h>

// Structure to store job details
typedef struct {
    char id;       // Job ID (A, B, C, ...)
    int deadline;  // Deadline for the job
    int profit;    // Profit if job is done before or on deadline
} Job;

// Compare function for sorting jobs in decreasing order of profit
int compare(const void *a, const void *b) {
    Job *jobA = (Job *)a;
    Job *jobB = (Job *)b;
    return (jobB->profit - jobA->profit);
}

// Function to find the maximum deadline among all jobs
int findMaxDeadline(Job jobs[], int n) {
    int max = jobs[0].deadline;
    for (int i = 1; i < n; i++) {
        if (jobs[i].deadline > max)
            max = jobs[i].deadline;
    }
    return max;
}

// Function to perform job sequencing
void jobSequencing(Job jobs[], int n) {
    // Sort jobs by profit in decreasing order
    qsort(jobs, n, sizeof(Job), compare);

    int maxDeadline = findMaxDeadline(jobs, n);
    int slot[maxDeadline];
    char result[maxDeadline];

    // Initialize all slots to empty
    for (int i = 0; i < maxDeadline; i++)
        slot[i] = 0;

    // Assign jobs to slots
    for (int i = 0; i < n; i++) {
        // Find a slot for this job (start from last possible)
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == 0) {  // If slot is free
                slot[j] = 1;
                result[j] = jobs[i].id;
                break;
            }
        }
    }

    // Display the result
    printf("\nJob Sequence for maximum profit: ");
    for (int i = 0; i < maxDeadline; i++) {
        if (slot[i])
            printf("%c ", result[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter number of jobs: ");
    scanf("%d", &n);

    Job jobs[n];
    printf("Enter job details (ID Deadline Profit):\n");
    for (int i = 0; i < n; i++) {
        scanf(" %c %d %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }

    jobSequencing(jobs, n);

    return 0;
}
