#include <stdlib.h>
#include <stdio.h>

// Process structure in scheduling unit of operating system (OS)
typedef struct process
{
    unsigned int process_id;
    unsigned int arrival_time;
    unsigned int CPU_burst_time_1;
    unsigned int IO_burst_time;
    unsigned int CPU_burst_time_2;
    int response_time;    // Beginning of first CPU burst time
    int turn_around_time; // Time from arrival to termination
    int waiting_time;     // Time spent in ready queue
    int termination_time; // Time when process is terminated
} Process;

// Create a new process with given parameters
Process *create_new_process(unsigned int process_id, unsigned int arrival_time, unsigned int CPU_burst_time_1, unsigned int IO_burst_time, unsigned int CPU_burst_time_2)
{
    Process *process = (Process *)malloc(sizeof(Process));

    process->process_id = process_id;
    process->arrival_time = arrival_time;
    process->CPU_burst_time_1 = CPU_burst_time_1;
    process->IO_burst_time = IO_burst_time;
    process->CPU_burst_time_2 = CPU_burst_time_2;
    process->response_time = -1;
    process->turn_around_time = -1;
    process->waiting_time = -1;
    process->termination_time = -1;

    return process;
}

// Copy a process to a new process with same parameters and return the new process
Process *copy_process(Process *process)
{
    Process *new_process = (Process *)malloc(sizeof(Process));
    new_process->process_id = process->process_id;
    new_process->arrival_time = process->arrival_time;
    new_process->CPU_burst_time_1 = process->CPU_burst_time_1;
    new_process->IO_burst_time = process->IO_burst_time;
    new_process->CPU_burst_time_2 = process->CPU_burst_time_2;
    new_process->response_time = process->response_time;
    new_process->turn_around_time = process->turn_around_time;
    new_process->waiting_time = process->waiting_time;
    new_process->termination_time = process->termination_time;
    return new_process;
}

// Print a process with all its parameters in a single line in the console window
void print_process(Process *process)
{
    printf("Process ID: %d | Arrival Time: %d | CPU Burst Time 1: %d | IO Burst Time: %d | CPU Burst Time 2: %d | Response Time: %d | Turn Around Time: %d | Waiting Time: %d | Termination Time: %d\n", process->process_id, process->arrival_time, process->CPU_burst_time_1, process->IO_burst_time, process->CPU_burst_time_2, process->response_time, process->turn_around_time, process->waiting_time, process->termination_time);
}