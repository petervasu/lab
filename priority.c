#include <stdio.h>

struct process
{
    int PID, PT, BT, WT, TAT;
};

struct process a[10];
struct process temp;

int main()
{
    int i, j, n;
    float total_WT = 0.0, total_TAT = 0.0, avg_WT = 0.0, avg_TAT = 0.0;

    printf("Enter the number of processes:\n");
    scanf("%d", &n);

    printf("PID BT PT:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d%d%d", &a[i].PID, &a[i].BT, &a[i].PT);
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j].PT > a[j + 1].PT)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    a[0].WT = 0;
    for (i = 1; i < n; i++)
    {
        a[i].WT = a[i - 1].WT + a[i - 1].BT;
        total_WT += a[i].WT;
    }

    printf("\nProcess ID | Priority | Burst Time | Waiting Time | Turnaround Time\n");

    for (i = 0; i < n; i++)
    {
        a[i].TAT = a[i].WT + a[i].BT;
        total_TAT += a[i].TAT;
        printf("\n%d %d %d %d %d\n", a[i].PID, a[i].PT, a[i].BT, a[i].WT, a[i].TAT);
    }

    avg_TAT = total_TAT / n;
    avg_WT = total_WT / n;

    printf("\ntotal waiting time: %f", total_WT);
    printf("\ntotal turnaround time: %f", total_TAT);
    printf("\naverage waiting time: %f", avg_WT);
    printf("\naverage turnaround time: %f", avg_TAT);
}