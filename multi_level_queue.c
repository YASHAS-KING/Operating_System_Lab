#include <stdio.h>
#define MAX 10
typedef struct {
    int pid, at, bt, type, start, ct, tat, wt, rt;
} Process;
void sortByAT(Process proc[], int idx[], int count) {
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (proc[idx[j]].at > proc[idx[j + 1]].at) {
                int tmp = idx[j];
                idx[j] = idx[j + 1];
                idx[j + 1] = tmp;
            }
}
int main() {
    int n;
    Process proc[MAX];
    int sysQ[MAX], sysCount = 0;
    int usrQ[MAX], usrCount = 0;
    printf("=== Multilevel Queue Scheduling (System > User, FCFS) ===\n\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d (PID AT BT): ", i + 1);
        scanf("%d %d %d", &proc[i].pid, &proc[i].at, &proc[i].bt);
        printf("  Type (0=System, 1=User): "); scanf("%d", &proc[i].type);
        if (proc[i].type == 0) sysQ[sysCount++] = i;
        else                   usrQ[usrCount++] = i;
    }
    sortByAT(proc, sysQ, sysCount);
    sortByAT(proc, usrQ, usrCount);
    int time = 0;
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < sysCount; i++) {
        int p = sysQ[i];
        if (time < proc[p].at) time = proc[p].at;
        proc[p].start = time;
        proc[p].rt    = proc[p].start - proc[p].at;
        printf(" P%d(S) |", proc[p].pid);
        time         += proc[p].bt;
        proc[p].ct    = time;
        proc[p].tat   = proc[p].ct  - proc[p].at;
        proc[p].wt    = proc[p].tat - proc[p].bt;
    }
    for (int i = 0; i < usrCount; i++) {
        int p = usrQ[i];
        if (time < proc[p].at) time = proc[p].at;
        proc[p].start = time;
        proc[p].rt    = proc[p].start - proc[p].at;
        printf(" P%d(U) |", proc[p].pid);
        time         += proc[p].bt;
        proc[p].ct    = time;
        proc[p].tat   = proc[p].ct  - proc[p].at;
        proc[p].wt    = proc[p].tat - proc[p].bt;
    }
    printf("\n\n");
    float totalTAT = 0, totalWT = 0, totalRT = 0;
    printf("%-6s %-6s %-6s %-8s %-6s %-6s %-6s %-6s\n",
           "PID", "AT", "BT", "Type", "CT", "TAT", "WT", "RT");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < sysCount; i++) {
        int p = sysQ[i];
        printf("%-6d %-6d %-6d %-8s %-6d %-6d %-6d %-6d\n",
               proc[p].pid, proc[p].at, proc[p].bt,
               "System", proc[p].ct, proc[p].tat, proc[p].wt, proc[p].rt);
        totalTAT += proc[p].tat;
        totalWT  += proc[p].wt;
        totalRT  += proc[p].rt;
    }
    for (int i = 0; i < usrCount; i++) {
        int p = usrQ[i];
        printf("%-6d %-6d %-6d %-8s %-6d %-6d %-6d %-6d\n",
               proc[p].pid, proc[p].at, proc[p].bt,
               "User", proc[p].ct, proc[p].tat, proc[p].wt, proc[p].rt);
        totalTAT += proc[p].tat;
        totalWT  += proc[p].wt;
        totalRT  += proc[p].rt;
    }
    printf("----------------------------------------------------\n");
    printf("Average Turnaround Time : %.2f\n", totalTAT / n);
    printf("Average Waiting Time    : %.2f\n", totalWT  / n);
    printf("Average Response Time   : %.2f\n", totalRT  / n);
    return 0;
}
