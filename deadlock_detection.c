#include <stdio.h>
#include <stdbool.h>

void detectDeadlock(int P, int R, int processes[], int available[], int allocation[][R], int request[][R]) {
    int work[R];
    bool finish[P];
    int deadlocked_processes[P];
    int safe_sequence[P]; 
    int deadlock_count = 0;
    int safe_count = 0;  
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < P; i++) {
        bool has_allocation = false;
        for (int j = 0; j < R; j++) {
            if (allocation[i][j] != 0) {
                has_allocation = true;
                break;
            }
        }
        finish[i] = !has_allocation; 
    }

    bool progress = true;
    while (progress) {
        progress = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < R; j++) {
                    if (request[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safe_sequence[safe_count++] = processes[i]; 
                    progress = true;
                }
            }
        }
    }
    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            deadlocked_processes[deadlock_count++] = processes[i];
        }
    }

    printf("\n--- RESULTS ---\n");
    if (deadlock_count > 0) {
        printf("System is in a DEADLOCK state.\n");
        printf("Deadlocked processes: ");
        for (int i = 0; i < deadlock_count; i++) {
            printf("P%d ", deadlocked_processes[i]);
        }
        printf("\n");
    } else {
        printf("System is SAFE. No deadlock detected.\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < safe_count; i++) {
            printf("P%d", safe_sequence[i]);
            if (i < safe_count - 1) printf(" -> ");
        }
        printf("\n");
    }
}

int main() {
    int P, R;
    printf("Enter the number of processes: ");
    scanf("%d", &P);
    printf("Enter the number of resource types: ");
    scanf("%d", &R);

    int processes[P];
    for(int i = 0; i < P; i++) {
        processes[i] = i;
    }

    int available[R];
    printf("\nEnter the Available instances of each resource (space-separated):\n");
    for (int i = 0; i < R; i++) {
        scanf("%d", &available[i]);
    }

    int allocation[P][R];
    printf("\nEnter the Allocation Matrix (%d rows, %d columns):\n", P, R);
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    int request[P][R];
    printf("\nEnter the Request Matrix (%d rows, %d columns):\n", P, R);
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nRunning Deadlock Detection Algorithm...\n");
    detectDeadlock(P, R, processes, available, allocation, request);
    return 0;
}