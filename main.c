// CPU Scheduling Unit of Operating System

#include "./IO/User_Interaction_Unit.h"
#include "./Scheduling_Unit/scheduler.h"

int main()
{
    Queue *job_queue = read_processes_from_CSV_file("./IO/input/input_processes4.csv");
    sort_queue(job_queue);

    FCFS_scheduling_algorithm(copy_queue(job_queue));
    RR_scheduling_algorithm(copy_queue(job_queue));
    SJF_scheduling_algorithm(copy_queue(job_queue));
    SRTF_scheduling_algorithm(copy_queue(job_queue));
    MLFQ_scheduling_algorithm(copy_queue(job_queue));

    return 0;
}
