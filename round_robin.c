#include <stdio.h>

void main() {
    int i, n, at[10], rem_bt[15], tat[10], wt[10], bt[10], qt, count, temp, sq = 0;
    float awt = 0, atat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the burst time of all processes: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
    }

    printf("Enter the quantum time: ");
    scanf("%d", &qt);

    while (1) {
        for (i = 0, count = 0; i < n; i++) {
            temp = qt;
            if (rem_bt[i] == 0) {
                count++;
                continue;
            }
            if (rem_bt[i] > qt)
                rem_bt[i] = rem_bt[i] - qt;
            else if (rem_bt[i] >= 0) {
                temp = rem_bt[i];
                rem_bt[i] = 0;
            }
            sq = sq + temp;
            tat[i] = sq;
        }
        if (n == count)
            break;
    }

    printf("\nProcess\t| Burst time\t| Turnaround time\t| Waiting time\n");
    for (i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];
        awt = awt + wt[i];
        atat = atat + tat[i];
        printf("%d\t\t %d\t\t %d\t\t %d\n", (i + 1), bt[i], tat[i], wt[i]);
    }

    awt = awt / n;
    atat = atat / n;
    printf("Average waiting time = %f\n", awt);
    printf("Average turn around time = %f\n", atat);
}
