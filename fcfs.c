#include <stdio.h>

void fcfs(int n, int AT[], int BT[]);
void sjf(int n, int AT[], int BT[]);
void printGanttChart(int n, int CT[]);

int main() {
    int n;
    int AT[10], BT[10];

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &AT[i]);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &BT[i]);
    }

    printf("\nFCFS Scheduling:\n");
    fcfs(n, AT, BT);


    return 0;
}

void fcfs(int n, int AT[], int BT[]) {
    int CT[10], TAT[10], WT[10], totalTAT = 0, totalWT = 0;
    float avgTAT, avgWT;

    CT[0] = AT[0] + BT[0];
    for (int i = 1; i < n; i++) {
        CT[i] = CT[i - 1] + BT[i];
    }

    for (int i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        totalTAT += TAT[i];
        WT[i] = TAT[i] - BT[i];
        totalWT += WT[i];
    }

    avgTAT = (float)totalTAT / n;
    avgWT = (float)totalWT / n;

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }
    printf("Average Turn Around Time: %f\n", avgTAT);
    printf("Average Waiting Time: %f\n", avgWT);

    printGanttChart(n, CT);
}


void printGanttChart(int n, int CT[]) {
    printf("\t\t\t Gantt Chart \t\t\t\n");
    printf("0");
    for (int i = 0; i < n; i++) {
        printf("  P%d  %d", i + 1, CT[i]);
    }
    printf("\n");
}