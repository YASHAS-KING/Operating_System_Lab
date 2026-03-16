#include<stdio.h>
#include<stdbool.h>
struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
    int in_queue;
    int is_first_time;
};
int queue[10000];
int front=0,rear=0;
void enqueue(int process_index){
    queue[rear++]=process_index;
}
int dequeue(){
    if(front==rear)return -1;
    return queue[front++];
}
bool is_empty(){
    return front==rear;
}
void display_queue(struct Process p[]) {
    printf("Ready Queue: [ ");
    for (int i = front; i < rear; i++) {
        printf("P%d ", p[queue[i]].process_id);
    }
    printf("]\n");
}
int main() {
    int n, tq;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    float total_wt = 0, total_tat = 0, total_rt = 0;
    for (int i = 0; i < n; i++) {
        p[i].process_id = i + 1;
        printf("\nProcess %d\n", p[i].process_id);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
        p[i].completion_time = 0;
        p[i].waiting_time = 0;
        p[i].turn_around_time = 0;
        p[i].in_queue = 0;
        p[i].is_first_time = 1;
    }
    printf("\nEnter the Time Quantum (TQ): ");
    scanf("%d", &tq);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    int current_time = 0;
    int completed = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].arrival_time <= current_time && p[i].in_queue == 0) {
            enqueue(i);
            p[i].in_queue = 1;
        }
    }
    while (completed < n) {
        if (is_empty()) {
            current_time++;
            for (int i = 0; i < n; i++) {
                if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && p[i].in_queue == 0) {
                    enqueue(i);
                    p[i].in_queue = 1;
                }
            }
            continue;
        }
        display_queue(p);
        int curr = dequeue();
        p[curr].in_queue = 0;
        if (p[curr].is_first_time == 1) {
            p[curr].response_time = current_time - p[curr].arrival_time;
            p[curr].is_first_time = 0;
        }
        if (p[curr].remaining_time > tq) {
            current_time += tq;
            p[curr].remaining_time -= tq;
            for (int i = 0; i < n; i++) {
                if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && p[i].in_queue == 0 && i != curr) {
                    enqueue(i);
                    p[i].in_queue = 1;
                }
            }
            enqueue(curr);
            p[curr].in_queue = 1;
        }
        else {
            current_time += p[curr].remaining_time;
            p[curr].remaining_time = 0;
            p[curr].completion_time = current_time;
            completed++;
            for (int i = 0; i < n; i++) {
                if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && p[i].in_queue == 0) {
                    enqueue(i);
                    p[i].in_queue = 1;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;

        total_tat += p[i].turn_around_time;
        total_wt += p[i].waiting_time;
        total_rt += p[i].response_time;
    }
    printf("\n----------------------------------------------------------------------------------------------------------\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\t\tResponse\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (p[j].process_id == i + 1) {
                printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n",
                       p[j].process_id,
                       p[j].arrival_time,
                       p[j].burst_time,
                       p[j].completion_time,
                       p[j].turn_around_time,
                       p[j].waiting_time,
                       p[j].response_time);
                break;
            }
        }
    }
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("\nTime Quantum used: %d\n", tq);
    printf("Average Turn Around Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Response Time: %.2f\n", total_rt / n);
    return 0;
}
