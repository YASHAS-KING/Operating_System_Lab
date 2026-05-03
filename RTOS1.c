#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TASKS 10
#define MAX_TIME  100
typedef struct {
    int id, C, P, next_arrival, remaining_time, deadline_miss;
} Task;
int compare_period(const void *a, const void *b) {
    return ((Task *)a)->P - ((Task *)b)->P;
}
void print_gantt(int gantt[], int max_time, int n_tasks, Task tasks[]) {
    printf("\n--- Gantt Chart ---\nTime: ");
    for (int t = 0; t < max_time; t++) printf("%3d", t);
    printf("\n");
    for (int i = 0; i < n_tasks; i++) {
        printf("T%d  : ", tasks[i].id);
        for (int t = 0; t < max_time; t++) printf(gantt[t] == tasks[i].id ? "  #" : "  .");
        printf("\n");
    }
    printf("CPU : ");
    for (int t = 0; t < max_time; t++) {
        if (gantt[t] == -1) printf("  _"); else printf(" T%d", gantt[t]);
    }
    printf("\n");
}
int main() {
    int n;
    Task tasks[MAX_TASKS];
    printf("=== Rate Monotonic Scheduling Simulator ===\n\nEnter number of tasks (max %d): ", MAX_TASKS);
    scanf("%d", &n);
    if (n <= 0 || n > MAX_TASKS) { printf("Invalid number of tasks.\n"); return 1; }
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("\nTask T%d:\n  Execution time (C%d): ", i + 1, i + 1);
        scanf("%d", &tasks[i].C);
        printf("  Period        (P%d): ", i + 1);
        scanf("%d", &tasks[i].P);
        if (tasks[i].C <= 0 || tasks[i].P <= 0 || tasks[i].C > tasks[i].P) {
            printf("Invalid: ensure C > 0, P > 0, and C <= P.\n"); return 1;
        }
        tasks[i].next_arrival = tasks[i].remaining_time = tasks[i].deadline_miss = 0;
    }
    qsort(tasks, n, sizeof(Task), compare_period);
    printf("\n--- Priority Assignment (lower index = higher priority) ---\n%-8s %-8s %-8s %-12s\n", "Task", "C", "P", "Priority");
    for (int i = 0; i < n; i++) printf("T%-7d %-8d %-8d %-12d\n", tasks[i].id, tasks[i].C, tasks[i].P, i + 1);
    double util = 0.0;
    for (int i = 0; i < n; i++) util += (double)tasks[i].C / tasks[i].P;
    printf("\nUtilization: %.4f\n", util);
    int lcm = 1;
    for (int i = 0; i < n; i++) {
        int a = lcm, b = tasks[i].P;
        while (b) { int t = b; b = a % b; a = t; }
        lcm = lcm / a * tasks[i].P;
        if (lcm > MAX_TIME) { lcm = MAX_TIME; break; }
    }
    int max_time = lcm, gantt[MAX_TIME];
    memset(gantt, -1, sizeof(gantt));
    for (int i = 0; i < n; i++) tasks[i].next_arrival = tasks[i].remaining_time = 0;
    printf("\nSimulation length: %d time units\n\n--- Scheduling Log ---\n%-6s %-12s %-10s\n", max_time, "Time", "Running", "Event");
    for (int time = 0; time < max_time; time++) {
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                if (tasks[i].remaining_time > 0) {
                    printf("t=%-4d %-12s DEADLINE MISS for T%d!\n", time, "---", tasks[i].id);
                    tasks[i].deadline_miss++;
                }
                tasks[i].remaining_time = tasks[i].C;
                tasks[i].next_arrival  += tasks[i].P;
            }
        }
        int current = -1;
        for (int i = 0; i < n; i++) { if (tasks[i].remaining_time > 0) { current = i; break; } }
        if (current != -1) {
            gantt[time] = tasks[current].id;
            tasks[current].remaining_time--;
            printf("t=%-4d T%-11d (remaining: %d)\n", time, tasks[current].id, tasks[current].remaining_time);
        } else {
            gantt[time] = -1;
            printf("t=%-4d %-12s\n", time, "IDLE");
        }
    }
    print_gantt(gantt, max_time, n, tasks);
    printf("\n--- Summary ---\n");
    int any_miss = 0;
    for (int i = 0; i < n; i++) {
        printf("T%d: %d deadline miss(es)\n", tasks[i].id, tasks[i].deadline_miss);
        if (tasks[i].deadline_miss > 0) any_miss = 1;
    }
    printf(any_miss ? "Deadline misses detected.\n" : "All deadlines met. Schedule is feasible.\n");
    return 0;
}