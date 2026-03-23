#include <stdio.h>
#include <math.h>
#define MAX_TASKS 10
typedef struct {
    int id;
    int C;
    int P;
    int remaining_time;
    int next_arrival;
} Task;
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}
int findHyperperiod(Task tasks[], int n) {
    int result = tasks[0].P;
    for (int i = 1; i < n; i++) {
        result = lcm(result, tasks[i].P);
    }
    return result;
}
void sortByPeriod(Task tasks[], int n) {
    Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].P > tasks[j].P) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}
int main() {
    int n;
    Task tasks[MAX_TASKS];
    float cpu_util = 0;

    printf("Enter number of tasks: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;

        printf("\nTask %d:\n", i + 1);
        printf("Execution Time (C): ");
        scanf("%d", &tasks[i].C);

        printf("Period (P): ");
        scanf("%d", &tasks[i].P);

        tasks[i].remaining_time = 0;
        tasks[i].next_arrival = 0;

        cpu_util += (float)tasks[i].C / tasks[i].P;
    }
    sortByPeriod(tasks, n);
    int hyper = findHyperperiod(tasks, n);

    int gantt[hyper];

    printf("\nHyperperiod = %d\n", hyper);
    printf("\n--- Scheduling Start ---\n");
    for (int time = 0; time < hyper; time++) {
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].C;
                tasks[i].next_arrival += tasks[i].P;
            }
        }
        int current = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                current = i;
                break;
            }
        }
        if (current != -1) {
            printf("Time %d: T%d\n", time, tasks[current].id);
            tasks[current].remaining_time--;
            gantt[time] = tasks[current].id;
        } else {
            printf("Time %d: Idle\n", time);
            gantt[time] = 0;
        }


        for (int i = 0; i < n; i++) {
            if (time >= tasks[i].next_arrival &&
                tasks[i].remaining_time > 0) {
                printf("Deadline Missed: T%d at time %d\n",
                       tasks[i].id, time);
            }
        }
    }

    printf("\n--- Scheduling End ---\n");


    printf("\nGantt Chart:\n");

    for (int i = 0; i < hyper; i++)
        printf("----");
    printf("\n|");

    for (int i = 0; i < hyper; i++) {
        if (gantt[i] == 0)
            printf(" I |");
        else
            printf("T%d |", gantt[i]);
    }

    printf("\n");

    for (int i = 0; i < hyper; i++)
        printf("----");

    printf("\n");

    for (int i = 0; i <= hyper; i++)
        printf("%-4d", i);

    printf("\n");


    printf("\nCPU Utilization = %.2f\n", cpu_util);

    float bound = n * (pow(2, (float)1/n) - 1);
    printf("RMS Bound = %.2f\n", bound);

    if (cpu_util <= bound)
        printf("Schedulable under RMS\n");
    else
        printf("May NOT be schedulable under RMS\n");

    return 0;
}