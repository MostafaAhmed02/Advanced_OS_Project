#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CYLINDERS 5000

// Helper for sorting
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// FCFS implementation
int fcfs(int requests[], int head, int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += abs(requests[i] - head);
        head = requests[i];
    }
    return total;
}

// SCAN implementation
int scan(int requests[], int head, int size) {
    int total = 0;
    int* sorted = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) sorted[i] = requests[i];
    qsort(sorted, size, sizeof(int), compare);

    int index = 0;
    while (index < size && sorted[index] < head) index++;

    for (int i = index; i < size; i++) {
        total += abs(sorted[i] - head);
        head = sorted[i];
    }

    if (head != CYLINDERS - 1) {
        total += (CYLINDERS - 1 - head);
        head = CYLINDERS - 1;
    }

    for (int i = index - 1; i >= 0; i--) {
        total += abs(sorted[i] - head);
        head = sorted[i];
    }

    free(sorted);
    return total;
}

// C-SCAN implementation
int cscan(int requests[], int head, int size) {
    int total = 0;
    int* sorted = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) sorted[i] = requests[i];
    qsort(sorted, size, sizeof(int), compare);

    int index = 0;
    while (index < size && sorted[index] < head) index++;

    for (int i = index; i < size; i++) {
        total += abs(sorted[i] - head);
        head = sorted[i];
    }

    if (head != CYLINDERS - 1) {
        total += (CYLINDERS - 1 - head);
        head = CYLINDERS - 1;
    }

    total += CYLINDERS - 1;
    head = 0;

    for (int i = 0; i < index; i++) {
        total += abs(sorted[i] - head);
        head = sorted[i];
    }

    free(sorted);
    return total;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <initial_head_position>\n", argv[0]);
        return 1;
    }

    int head = atoi(argv[1]);
    if (head < 0 || head >= CYLINDERS) {
        printf("Error: Initial head position must be between 0 and 4999.\n");
        return 1;
    }

    int num_requests;
    printf("Enter the number of cylinder requests: ");
    scanf("%d", &num_requests);

    if (num_requests <= 0) {
        printf("Request size must be greater than zero.\n");
        return 1;
    }

    int* requests = (int*)malloc(num_requests * sizeof(int));
    if (requests == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < num_requests; i++) {
        requests[i] = rand() % CYLINDERS;
    }

    int choice;
    printf("Select Algorithm:\n");
    printf("1. FCFS\n2. SCAN\n3. C-SCAN\nEnter choice: ");
    scanf("%d", &choice);

    int total_seek = 0;
    switch (choice) {
    case 1:
        total_seek = fcfs(requests, head, num_requests);
        printf("FCFS Total Head Movement: %d\n", total_seek);
        break;
    case 2:
        total_seek = scan(requests, head, num_requests);
        printf("SCAN Total Head Movement: %d\n", total_seek);
        break;
    case 3:
        total_seek = cscan(requests, head, num_requests);
        printf("C-SCAN Total Head Movement: %d\n", total_seek);
        break;
    default:
        printf("Invalid choice.\n");
    }

    free(requests);
    return 0;
}
