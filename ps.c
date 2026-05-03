#include <stdio.h>
struct Process {
    int pid;
    float arrival_time;
    float burst_time;
    float weight;
    float remaining_time;
    int is_completed;
    float completion_time;
    float turnaround_time;
    float waiting_time;
};
struct Gantt {
    int pid;
    float start;
    float end;
};

int main() {
    int n;
    float time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the Base Time Quantum: ");
    scanf("%f", &time_quantum);
    struct Process p[n];
    struct Gantt chart[100];
    int chart_count = 0;
    float total_weight = 0.0;
    float total_tat = 0.0, total_wt = 0.0;
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d\n", p[i].pid);
        printf("Enter Arrival Time: ");
        scanf("%f", &p[i].arrival_time);
        printf("Enter Burst Time: ");
        scanf("%f", &p[i].burst_time);
        printf("Enter Weight: ");
        scanf("%f", &p[i].weight);
        p[i].remaining_time = p[i].burst_time;
        p[i].is_completed = 0;
        total_weight += p[i].weight;
    }
    float current_time = 0.0;
    int completed_processes = 0;
    while (completed_processes < n) {
        int executed_any = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].is_completed == 0) {
                if (total_weight <= 0) break;

                float time_slice = (p[i].weight / total_weight) * time_quantum;

                if (p[i].remaining_time < time_slice) {
                    time_slice = p[i].remaining_time;
                }
                chart[chart_count].pid = p[i].pid;
                chart[chart_count].start = current_time;

                current_time += time_slice;
                p[i].remaining_time -= time_slice;

                chart[chart_count].end = current_time;
                chart_count++;

                executed_any = 1;

                if (p[i].remaining_time <= 0.0001) {
                    p[i].remaining_time = 0;
                    p[i].is_completed = 1;
                    completed_processes++;

                    p[i].completion_time = current_time;
                    p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

                    total_tat += p[i].turnaround_time;
                    total_wt += p[i].waiting_time;

                    total_weight -= p[i].weight;
                }
            }
        }

        if (executed_any == 0) {
            chart[chart_count].pid = 0;
            chart[chart_count].start = current_time;
            current_time += 1.0;
            chart[chart_count].end = current_time;
            chart_count++;
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------\n");
    printf("PID\tArrival\t\tBurst\t\tWeight\t\tCompletion\tTurnaround\tWaiting\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].weight,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("\n--- GANTT CHART ---\n\n ");
    for (int i = 0; i < chart_count; i++) printf("-------");
    printf("\n|");
    for (int i = 0; i < chart_count; i++) {
        if (chart[i].pid == 0) printf(" IDLE |");
        else printf("  P%d  |", chart[i].pid);
    }
    printf("\n ");
    for (int i = 0; i < chart_count; i++) printf("-------");
    printf("\n0.00");
    for (int i = 0; i < chart_count; i++) {
        printf("   %.2f", chart[i].end);
    }

    printf("\n\nAverage Turn Around Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
