#include<stdio.h>
#include<limits.h>
struct process{
    int p_id;
    int at;
    int bt;
    int priority_no;
    int rem_time;
    int ct;
    int tat;
    int wt;
    int rt;
    int is_started;
};
int main(){
    int n;
    printf("enter the no of processes: ");
    scanf("%d",&n);
    struct process p[n];
    float total_wt=0,total_tat=0,total_rt=0;
    for(int i=0;i<n;i++){
        p[i].p_id=i+1;
        printf("\n process %d\n",p[i].p_id);
        printf("enter arrival time: ");
        scanf("%d",&p[i].at);
        printf("enter the burst time: ");
        scanf("%d",&p[i].bt);
        printf("enter the priority_no: ");
        scanf("%d",&p[i].priority_no);
        p[i].rem_time=p[i].bt;
        p[i].is_started=0;
    }
    int current_time=0;
    int completed_processes=0;
    while(completed_processes<n){
        int highest_priority=INT_MAX;
        int shortest_process_index=-1;
        for(int i=0;i<n;i++){
            if(p[i].at<=current_time && p[i].rem_time>0){
                if(p[i].priority_no<highest_priority){
                    highest_priority=p[i].priority_no;
                    shortest_process_index=i;
                }
                else if(p[i].priority_no==highest_priority){
                    if(p[i].at<p[shortest_process_index].at){
                        shortest_process_index=i;
                    }
                }
            }
        }
        if(shortest_process_index!=-1){
            int i=shortest_process_index;
            if(p[i].is_started==0){
                p[i].rt=current_time-p[i].at;
                p[i].is_started=1;
            }
            p[i].rem_time--;
            if(p[i].rem_time==0){
                completed_processes++;
                p[i].ct=current_time+1;
                p[i].tat=p[i].ct-p[i].at;
                p[i].wt=p[i].tat-p[i].bt;
                total_tat+=p[i].tat;
                total_wt+=p[i].wt;
                total_rt+=p[i].rt;
            }
        }
        current_time++;
    }
    printf("pid\tarrival\tburst\tcompletion\tturnaround\twaiting\tresponse\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n",
               p[i].p_id,
               p[i].at,
               p[i].bt,
               p[i].priority_no,
               p[i].ct,
               p[i].tat,
               p[i].wt,
               p[i].rt);
    }
    printf("\n Avg turnaround time:%.2f",total_tat/n);
    printf("\n Avg waiting time:%.2f",total_wt/n);
    printf("\nAvg response time:%.2f",total_rt/n);
    return 0;
}
