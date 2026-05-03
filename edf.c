#include <stdio.h>
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int deadline;
    int abs_deadline;
    int remaining_time;
    int is_completed;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    float utilization = 0.0;
    float total_tat = 0, total_wt = 0;
    int total_burst = 0;

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d\n", p[i].pid);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Enter Burst Time (Ci): ");
        scanf("%d", &p[i].burst_time);
        printf("Enter Deadline/Period (Di): ");
        scanf("%d", &p[i].deadline);

        p[i].remaining_time = p[i].burst_time;
        p[i].abs_deadline = p[i].arrival_time + p[i].deadline;
        p[i].is_completed = 0;
        utilization += (float)p[i].burst_time / p[i].deadline;
        total_burst += p[i].burst_time;
    }

    printf("\n--------------------------------------------------\n");
    printf("CPU Utilization: %.4f\n", utilization);
    if (utilization > 1.0) {
        printf("Result: Scheduling not feasible (deadlines may be missed).\n");
    } else {
        printf("Result: Scheduling feasible.\n");
    }
    printf("--------------------------------------------------\n");
    int current_time = 0;
    int completed_processes = 0;
    int gantt_chart[200];
    int time_log = 0;
    while (completed_processes < n) {
        int min_deadline = 9999999;
        int selected_process_index = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].is_completed == 0) {
                if (p[i].abs_deadline < min_deadline) {
                    min_deadline = p[i].abs_deadline;
                    selected_process_index = i;
                }
            }
        }

        if (selected_process_index == -1) {
            gantt_chart[time_log++] = 0; // 0 represents Idle time
            current_time++;
        } else {
            int i = selected_process_index;
            gantt_chart[time_log++] = p[i].pid;
            p[i].remaining_time--;
            current_time++;

            if (p[i].remaining_time == 0) {
                p[i].is_completed = 1;
                completed_processes++;
                p[i].completion_time = current_time;
                p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
                p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                total_tat += p[i].turnaround_time;
                total_wt += p[i].waiting_time;

                if (p[i].completion_time > p[i].abs_deadline) {
                    printf("\n[WARNING] Process %d missed its deadline! (Completed at %d, Deadline %d)\n",
                           p[i].pid, p[i].completion_time, p[i].abs_deadline);
                }
            }
        }
    }
    printf("\n------------------------------------------------------------------------------------------------------\n");
    printf("PID\tArrival\tBurst\tRel. Dline\tAbs. Dline\tCompletion\tTurnaround\tWaiting\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].deadline,
               p[i].abs_deadline, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("\nGANTT CHART\n");
    printf(" ");
    for (int i = 0; i < time_log; i++) printf("--- ");
    printf("\n|");
    for (int i = 0; i < time_log; i++) {
        if (gantt_chart[i] == 0) printf(" ID |");
        else printf(" P%d |", gantt_chart[i]);
    }
    printf("\n ");
    for (int i = 0; i < time_log; i++) printf("--- ");
    printf("\n0");
    for (int i = 0; i < time_log; i++) {
        if (i + 1 > 9) printf("  %d", i + 1);
        else printf("   %d", i + 1);
    }

    printf("\n\nAverage Turn Around Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
