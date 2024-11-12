#include<stdio.h>

int main() {
    int i, sum = 0, gt[20], qt, n, bt[20], tt[20], wt[20], bt_cp[20], p[20], at[20], temp, count = 0, l = 0, k = 1, time[20] = {0};
    float wt_avg = 0, tt_avg = 0;

    printf("\nEnter the number of Processes(Max 20): ");
    scanf("%d", &n);

    printf("\nEnter the Arrival Time and Burst Time of Each Process:\n");
    for (int j = 0; j < n; j++) {
        p[j] = j + 1;
        printf("P%d : ", j + 1);
        scanf("%d %d", &at[j], &bt[j]);
        bt_cp[j] = bt[j];
    }

    printf("\nEnter the Time Slice: ");
    scanf("%d", &qt);

    int current_time = 0;
    while (count != n) {
        for (i = 0, count = 0; i < n; i++) {
            if (bt_cp[i] == 0) {
                count++;
                continue;
            }
            if (at[i] <= current_time) {
                if (bt_cp[i] > qt) {
                    bt_cp[i] -= qt;
                    temp = qt;
                } else if (bt_cp[i] <= qt && bt_cp[i] > 0) {
                    temp = bt_cp[i];
                    bt_cp[i] = 0;
                }
                current_time += temp;
                sum += temp;
                tt[i] = current_time - at[i];
                gt[l++] = p[i];
                time[k] = current_time;
                k++;
            }
        }
    }

    for (i = 0; i < n; i++) {
        wt[i] = tt[i] - bt[i];
        wt_avg += wt[i];
        tt_avg += tt[i];
    }

    wt_avg /= n;
    tt_avg /= n;

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i], at[i], bt[i], wt[i], tt[i]);

    printf("\nAverage Waiting Time: %.2f ms", wt_avg);
    printf("\nAverage Turnaround Time: %.2f ms\n", tt_avg);

    printf("\n\n\t\t\t\tGantt Chart\n\n");
    printf("------------------------------------------------------------------------\n");
    for (i = 0; i < l; i++)
        printf("|\tP%d\t|", gt[i]);
    printf("\n------------------------------------------------------------------------\n");
    for (i = 0; i < k; i++)
        printf("%d\t   \t", time[i]);
    printf("\n------------------------------------------------------------------------\n");

    return 0;
}