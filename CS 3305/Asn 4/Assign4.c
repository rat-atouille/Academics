#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int arrival_time;
    int burst_time;
    int wait_time;
    int turnaround_time;
    int remaining_time;
    int completed;
    int pid;
} Process;

void simulate_FCFS(Process *processes, int num_processes);
void simulate_SJF(Process *processes, int num_processes);
void simulate_RR(Process *processes, int num_processes, int quantum);

int main(int argc, char *argv[]) {

    char *algorithm = argv[1];
    int quantum = 0;
    
    // file doesn't exist
    char *filename = argv[argc - 1];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return 1;
    }

    int num_processes=20;
    char line[20];
    int n = 0;
    Process processes[20];
    
    while (fgets(line, sizeof(line), file)) {
        processes[n].pid = atoi(strtok(line + 1, ","));
        processes[n].burst_time = atoi(strtok(NULL, ","));
        processes[n].completed = 0;
        processes[n].wait_time = 0;
        processes[n].turnaround_time = 0;
        processes[n].arrival_time = processes[n].pid;
        processes[n].remaining_time = processes[n].burst_time;
        //printf("Process: P %d, Burst Time: %d\n", processes[n].arrival_time, processes[n].burst_time);
        n++;
   }
    fclose(file);

    if (strcmp(algorithm, "-f") == 0) {
        simulate_FCFS(processes, n);
    } else if (strcmp(algorithm, "-s") == 0) {
        simulate_SJF(processes, n);
    } else if (strcmp(algorithm, "-r") == 0 && argc == 4) {
        int quantum = atoi(argv[2]);
        simulate_RR(processes, n, quantum);
    } else {
        printf("Error: Invalid algorithm or insufficient parameters\n");
        return 1;
    }
    return 0;
}

void simulate_FCFS(Process *processes, int n) {
    printf("First Come First Served\n");
    int current_time=0;
    int turnaround=0;
    int waitTime=0;
    float totalWait=0;
    float totalTurn=0;

    // iterate the array of processes
    for (int i=0; i<n;i++){
        processes[i].turnaround_time = turnaround;
        processes[i].wait_time = waitTime;
        totalWait += waitTime;

        // burst until remaining time = 0 and move to the next process
        while (processes[i].burst_time > 0) {
            printf("T%d : P%d - Burst left %d, Wait time %d, Turnaround Time %d \n", current_time,
            processes[i].pid, processes[i].burst_time, processes[i].wait_time, processes[i].turnaround_time);
            processes[i].burst_time--;
            processes[i].turnaround_time++;
            current_time++;
        }
        turnaround = processes[i].turnaround_time-1;
        totalTurn += turnaround+1;
        waitTime = turnaround;
        processes[i].completed = 1;
    }
    
    printf("\n *** CHECK *** \n");
    for (int i=0; i<n;i++){
        printf("P%d - Wait time %d, Turnaround Time %d \n", 
        processes[i].pid, processes[i].wait_time, processes[i].turnaround_time);
    }

    totalWait = totalWait/n;
    totalTurn = (totalTurn)/n;
    printf("Total average waiting time:     %.1f \n", totalWait);
    printf("Total average turnaround time:     %.1f \n", totalTurn );
}

void simulate_SJF(Process *processes, int n) {
    printf("Shortest Job First\n");

    // Sort processes based on burst time (Shortest Job First)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                // Swap burst time
                int temp_burst = processes[j].burst_time;
                processes[j].burst_time = processes[j + 1].burst_time;
                processes[j + 1].burst_time = temp_burst;

                // Swap PID
                int temp_pid = processes[j].pid;
                processes[j].pid = processes[j + 1].pid;
                processes[j + 1].pid = temp_pid;
            }
        }
    }

    // Simulate SJF
    int current_time = 0;
    float total_wait = 0;
    float total_turnaround = 0;
    int turnaround = 0;
    int waitTime = 0;
    int all_completed = 0;
    int t;
    // Iterate until all processes are completed
    while (all_completed < n) {
        int shortest_job_index = -1;
        int shortest_job_burst = INT_MAX;

        // Find the shortest job available at the current time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].completed == 0 && processes[i].burst_time < shortest_job_burst) {
                shortest_job_index = i;
                shortest_job_burst = processes[i].burst_time;
            }
        }

        if (shortest_job_index != -1) {
            processes[shortest_job_index].wait_time = current_time - processes[shortest_job_index].arrival_time;
            total_wait += processes[shortest_job_index].wait_time;
            processes[shortest_job_index].turnaround_time = processes[shortest_job_index].wait_time + processes[shortest_job_index].burst_time;
            total_turnaround += processes[shortest_job_index].turnaround_time;

            // Simulate execution of the shortest job
            current_time += processes[shortest_job_index].burst_time;
            processes[shortest_job_index].completed = 1;
            all_completed++;
        } else {
            // If no job is available, move to the next arrival time
            int next_arrival_time = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (processes[i].completed == 0 && processes[i].arrival_time < next_arrival_time) {
                    next_arrival_time = processes[i].arrival_time;
                }
            }
            current_time = next_arrival_time;
        }
    }

    for (int i =0; i<n;i++) {
        printf("P %d Wait time: %d, turnaround time: %d \n", 
        processes[i].pid, processes[i].wait_time, processes[i].turnaround_time);

    }
    // Calculate averages
    total_wait /= n;
    total_turnaround /= n;

    // Print results
    printf("Total average waiting time:     %.1f \n", total_wait);
    printf("Total average turnaround time:  %.1f \n", total_turnaround);
}

void simulate_RR(Process *processes, int n, int quantum) {
    printf("Round Robin with Quantum %d \n", quantum);
    int current_time=0, turnaround=0, waitTime=0;
    float totalWait=0;
    float totalTurn=0;
    int count;
    int all_completed = 0;
    int loop = 1;

    // repeat until all the processes finish
    while (all_completed < n) {
        printf("***Loop %d****\n", loop);
        // iterate the array of processes
        for (int i=0; i<n;i++){
            // simulate only if the process is incomplete
            if (processes[i].completed == 0) {
                processes[i].turnaround_time = turnaround;
                processes[i].wait_time = waitTime;
                count = 0;

                // burst quantum times
                while (processes[i].burst_time > 0 && count < quantum && processes[i].completed == 0) {
                    printf("T%d : P%d - Burst left %d, Wait time %d, Turnaround Time %d \n", current_time,
                    processes[i].pid, processes[i].burst_time, processes[i].wait_time, processes[i].turnaround_time);
                    processes[i].burst_time--;
                    processes[i].turnaround_time++;
                    current_time++;
                    count++;
                }
                turnaround = processes[i].turnaround_time-1;
                waitTime = turnaround;
            }
            
            // if its done, mark complete
            if (processes[i].burst_time == 0 && processes[i].completed != 1) {
                processes[i].completed = 1;
                all_completed ++;
            }
        }
        loop++;
    }
    
    // shows processes burst and turnaround time
    printf("\n *** CHECK *** \n");
    for (int i=0; i<n;i++){
        printf("P%d - Wait time %d, Turnaround Time %d \n", 
        processes[i].pid, processes[i].wait_time, processes[i].turnaround_time);
    }
    
    // average calculation
    for (int i = 0; i < n; i++) {
        totalWait += processes[i].wait_time;
        totalTurn += processes[i].turnaround_time+1;
    }
    
    float avg_wait_time = totalWait / n;
    float avg_turnaround_time = totalTurn / n;
    printf("Total average wait time:     %.1f \n", avg_wait_time);
    printf("Total average turnaround time:     %.1f \n", avg_turnaround_time);
}
