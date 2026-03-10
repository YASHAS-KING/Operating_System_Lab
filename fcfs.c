#include<stdio.h>
struct process{
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};
void sort_process(struct process p[],int n){
    struct process temp;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].at>p[j+1].at){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}
int main(){
    int n;
    float total_tat=0,total_wt=0;
    printf("enter number of processes:");
    scanf("%d",&n);
    struct process p[n];
    for(int i=0;i<n;i++){
        p[i].id=i+1;
        printf("enter arrival and burst time for process %d",p[i].id);
        scanf("%d %d",&p[i].at,&p[i].bt);
    }
    sort_process(p,n);
    int curr_time=0;
    for(int i=0;i<n;i++){
        if(curr_time<p[i].at){
            curr_time=p[i].at;
        }
        p[i].ct=curr_time+p[i].bt;
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        curr_time=p[i].ct;
        total_tat+=p[i].tat;
        total_wt+=p[i].wt;
    }
    printf("\npid\tat\tbt\tct\ttat\twt\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    printf("\n avg turnaround time: %.2f",total_tat/n);
    printf("\n average waiting time: %.2f\n",total_wt/n);
    return 0;
}
