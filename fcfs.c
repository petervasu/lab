#include<stdio.h>

int main()
{
    int pid[15], bt[15], n, i;
    
    printf("Enter the number of processes:");
    scanf("%d", &n);
    
    printf("Enter the process IDs of all processes:");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &pid[i]);
    }
    
    printf("Enter the burst time of all processes:");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
    }
    
    int wt[100];
    wt[0] = 0;
    for(i = 1; i < n; i++)
    {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
    
    printf("\nProcess ID | Burst Time | Waiting Time | Turnaround Time\n");
    float twt = 0.0, tat = 0.0;
    for(i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\n", pid[i], bt[i], wt[i], bt[i] + wt[i]);
        tat += (wt[i] + bt[i]);
        twt += wt[i];
    }
    
    float att, awt;
    awt = twt / n;
    att = tat / n;
    
    printf("Average waiting time = %f\n", awt);
    printf("Average turnaround time = %f", att);
    
    return 0;
}

