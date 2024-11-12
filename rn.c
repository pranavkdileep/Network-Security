// Online C compiler to run C program online
#include <stdio.h>

int main() {
    int n,count=0,p[10],at[10],bt[10],btc[10],tt[10],wt[10],gt[10],time[10],l=0,k=1,qt,t=0,temp;
    time[0] =0;
    float wt_avg,tt_avg;
    printf("Enter the number of Processes(Max 20): ");
    scanf("%d",&n);
    for (int j = 0; j < n; j++) {
        p[j] = j + 1;
        // printf("P%d : ", j + 1);
        scanf("%d %d", &at[j], &bt[j]);
        btc[j] = bt[j];
    }

    printf("\nEnter the Time Slice: ");
    scanf("%d", &qt);
    while(count!=n){
        for(int i=0;i<n;i++){
            if(btc[i] == 0){
                count++;
                continue;
            }
            if(at[i]<= t){
                if(btc[i] > qt) {
                    btc[i] -= qt;
                    temp = qt;
                }else
                if (btc[i] <= qt && btc[i] > 0) {
                    temp = btc[i];
                    btc[i] = 0;
                }
                t += temp;
                gt[l++] = p[i];
                time[k++] = t;
                tt[i] = t - at[i];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        wt[i] = tt[i] - bt[i];
        wt_avg += wt[i];
        tt_avg += tt[i];
    }
    
    wt_avg /= n;
    tt_avg /= n;
    
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i], at[i], bt[i], wt[i], tt[i]);

    printf("\nAverage Waiting Time: %.2f ms", wt_avg);
    printf("\nAverage Turnaround Time: %.2f ms\n", tt_avg);

    printf("\n\n\t\t\t\tGantt Chart\n\n");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < l; i++)
        printf("|\tP%d\t|", gt[i]);
    printf("\n------------------------------------------------------------------------\n");
    for (int i = 0; i < k; i++)
        printf("%d\t   \t", time[i]);
    printf("\n------------------------------------------------------------------------\n");

    return 0;
}