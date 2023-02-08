#include "./Analyze_Unit/algorithm_analyzer.h"

Queue *ready_queue = NULL;
Process *running_process = NULL;
Queue *waiting_queue = NULL;
Queue *terminated_queue = NULL;

// First Come, First Serve (FCFS) Scheduling Algorithm in Operating System
void FCFS_scheduling_algorithm(Queue *job_queue)
{
    create_directory("./IO/output/FCFS");
    FILE *algorithm_procedure_output_file = create_file("./IO/output/FCFS/", "FCFS - Algorithm Procedure", ".log");
    FILE *algorithm_analysis_output_file = create_file("./IO/output/FCFS/", "FCFS - Algorithm Analysis", ".log");
    FILE *processes_analysis_output_file = create_file("./IO/output/FCFS/", "FCFS - Processes Analysis", ".log");

    Queue *job_queue_copy = copy_queue(job_queue);
    ready_queue = create_new_queue(job_queue->capacity);
    running_process = NULL;
    waiting_queue = create_new_queue(job_queue->capacity);
    terminated_queue = create_new_queue(job_queue->capacity);

    int current_time = 0;

    fprintf(algorithm_procedure_output_file, "***First Come, First Serve (FCFS) Scheduling Algorithm in Operating System***\n\n");
    while (!is_full(terminated_queue))
    {
        fprintf(algorithm_procedure_output_file, "Time = %d-%d:\n", current_time, current_time + 1);

        if (!is_empty(job_queue) && front(job_queue)->arrival_time <= current_time)
        {
            enqueue(ready_queue, dequeue(job_queue));
            fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Job-Queue to Ready-Queue.\n", rear(ready_queue)->process_id);
        }

        if (!is_empty(ready_queue) && running_process == NULL)
        {
            running_process = dequeue(ready_queue);
            if (running_process->response_time == -1)
                running_process->response_time = current_time;
            fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Ready-Queue to Running-State.\n", running_process->process_id);
        }

        if (!is_empty(waiting_queue))
        {
            front(waiting_queue)->IO_burst_time--;
            fprintf(algorithm_procedure_output_file, "\tProcess-%d's Waited for I/O Recourse for 1 Second (Remaining I/O Waiting Time = %d).\n", front(waiting_queue)->process_id, front(waiting_queue)->IO_burst_time);
            if (front(waiting_queue)->IO_burst_time == 0)
            {
                enqueue(ready_queue, dequeue(waiting_queue));
                fprintf(algorithm_procedure_output_file, "\tProcess-%d's IO's Waiting Time Was Finished and Was Moved From Waiting-Queue to Ready-Queue.\n", rear(ready_queue)->process_id);
            }
        }

        if (running_process != NULL)
            if (running_process->CPU_burst_time_1 == 0)
            {
                if (running_process->IO_burst_time == 0 && running_process->CPU_burst_time_2 != 0)
                {
                    // Decrease the CPU burst time of the process in the running queue by 1
                    running_process->CPU_burst_time_2--;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d's Second CPU Burst Was Executed for 1 Second (Remaining Second CPU Burst Time = %d).\n", running_process->process_id, running_process->CPU_burst_time_2);
                    if (running_process->CPU_burst_time_2 == 0)
                    {
                        enqueue(terminated_queue, running_process);
                        running_process->termination_time = current_time + 1;
                        running_process->turn_around_time = running_process->termination_time - running_process->arrival_time;
                        running_process->waiting_time = running_process->turn_around_time - (running_process->CPU_burst_time_1 + running_process->IO_burst_time + running_process->CPU_burst_time_2);
                        running_process = NULL;
                        fprintf(algorithm_procedure_output_file, "\tProcess-%d Was Terminated (Moved From Running-State to Terminated-Queue).\n", rear(terminated_queue)->process_id);
                    }
                }
            }
            else
            {
                running_process->CPU_burst_time_1--;
                fprintf(algorithm_procedure_output_file, "\tProcess-%d's First CPU Burst Was Executed for 1 Second (Remaining First CPU Burst Time = %d).\n", running_process->process_id, running_process->CPU_burst_time_1);
                if (running_process->CPU_burst_time_1 == 0 && running_process->IO_burst_time != 0)
                {
                    enqueue(waiting_queue, running_process);
                    running_process = NULL;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Running-State to Waiting-Queue to Execute It's IO Burst.\n", rear(waiting_queue)->process_id);
                }
            }

        current_time++;
    }

    fclose(algorithm_procedure_output_file);

    analyze_algorithm(job_queue_copy, terminated_queue, algorithm_analysis_output_file);
    analyze_processes(job_queue_copy, terminated_queue, processes_analysis_output_file);

    fclose(algorithm_analysis_output_file);
    fclose(processes_analysis_output_file);
}

// Round-Robin (RR) Scheduling Algorithm in Operating System
void RR_scheduling_algorithm(Queue *job_queue)
{
    create_directory("./IO/output/RR");
    FILE *algorithm_procedure_output_file = create_file("./IO/output/RR/", "RR - Algorithm Procedure", ".log");
    FILE *algorithm_analysis_output_file = create_file("./IO/output/RR/", "RR - Algorithm Analysis", ".log");
    FILE *processes_analysis_output_file = create_file("./IO/output/RR/", "RR - Processes Analysis", ".log");

    Queue *job_queue_copy = copy_queue(job_queue);
    ready_queue = create_new_queue(job_queue->size);
    running_process = NULL;
    waiting_queue = create_new_queue(job_queue->size);
    terminated_queue = create_new_queue(job_queue->size);

    int current_time = 0;

    fprintf(algorithm_procedure_output_file, "***Round-Robin (RR) Scheduling Algorithm in Operating System***\n\n");

    int time_quantum;
    printf("Enter Time Quantum for Round-Robin (RR): ");
    scanf("%d", &time_quantum);
    int execution_elapsed_time = 0;

    while (!is_full(terminated_queue))
    {
        fprintf(algorithm_procedure_output_file, "Time = %d-%d:\n", current_time, current_time + 1);

        if (!is_empty(job_queue) && front(job_queue)->arrival_time <= current_time)
        {
            enqueue(ready_queue, dequeue(job_queue));
            fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Job-Queue to Ready-Queue.\n", rear(ready_queue)->process_id);
        }

        if (!is_empty(ready_queue) && running_process == NULL)
        {
            // Move the process from the ready queue to the running state
            running_process = dequeue(ready_queue);
            execution_elapsed_time = 0;
            if (running_process->response_time == -1)
                running_process->response_time = current_time;
            fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Ready-Queue to Running-State.\n", running_process->process_id);
        }

        if (!is_empty(waiting_queue))
        {
            front(waiting_queue)->IO_burst_time--;
            fprintf(algorithm_procedure_output_file, "\tProcess-%d's Waited for I/O Recourse for 1 Second (Remaining I/O Waiting Time = %d).\n", front(waiting_queue)->process_id, front(waiting_queue)->IO_burst_time);

            if (front(waiting_queue)->IO_burst_time == 0)
            {
                enqueue(ready_queue, dequeue(waiting_queue));
                fprintf(algorithm_procedure_output_file, "\tProcess-%d's IO's Waiting Time Was Finished and Was Moved From Waiting-Queue to Ready-Queue.\n", rear(ready_queue)->process_id);
            }
        }

        if (running_process != NULL)
            if (running_process->CPU_burst_time_1 == 0)
            {
                if (running_process->IO_burst_time == 0 && running_process->CPU_burst_time_2 != 0)
                {
                    running_process->CPU_burst_time_2--;
                    execution_elapsed_time++;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d's Second CPU Burst Was Executed for 1 Second (Remaining Second CPU Burst Time = %d).\n", running_process->process_id, running_process->CPU_burst_time_2);

                    if (running_process->CPU_burst_time_2 == 0)
                    {
                        enqueue(terminated_queue, running_process);
                        running_process->termination_time = current_time + 1;
                        running_process->turn_around_time = running_process->termination_time - running_process->arrival_time;
                        running_process->waiting_time = running_process->turn_around_time - (running_process->CPU_burst_time_1 + running_process->IO_burst_time + running_process->CPU_burst_time_2);
                        running_process = NULL;
                        fprintf(algorithm_procedure_output_file, "\tProcess-%d Was Terminated (Moved From Running-State to Terminated-Queue).\n", rear(terminated_queue)->process_id);
                    }

                    if (execution_elapsed_time == time_quantum)
                    {
                        enqueue(ready_queue, running_process);
                        running_process = NULL;
                        fprintf(algorithm_procedure_output_file, "\tProcess-%d's Time Quantum Was Finished and Was Moved From Running-State to Ready-Queue.\n", rear(ready_queue)->process_id);
                    }
                }
            }
            else
            {
                running_process->CPU_burst_time_1--;
                execution_elapsed_time++;
                fprintf(algorithm_procedure_output_file, "\tProcess-%d's First CPU Burst Was Executed for 1 Second (Remaining First CPU Burst Time = %d).\n", running_process->process_id, running_process->CPU_burst_time_1);

                if (running_process->CPU_burst_time_1 == 0 && running_process->IO_burst_time != 0)
                {
                    enqueue(waiting_queue, running_process);
                    running_process = NULL;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Running-State to Waiting-Queue to Execute It's IO Burst.\n", rear(waiting_queue)->process_id);
                }
                else if (execution_elapsed_time == time_quantum)
                {
                    enqueue(ready_queue, running_process);
                    running_process = NULL;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d's Time Quantum Was Finished and Was Moved From Running-State to Ready-Queue.\n", rear(ready_queue)->process_id);
                }
            }

        current_time++;
    }

    fclose(algorithm_procedure_output_file);

    analyze_algorithm(job_queue_copy, terminated_queue, algorithm_analysis_output_file);
    analyze_processes(job_queue_copy, terminated_queue, processes_analysis_output_file);

    fclose(algorithm_analysis_output_file);
    fclose(processes_analysis_output_file);
}

// Shortest Job First (SJF) or Shortest Process Next (SPN) Scheduling Algorithm
void SJF_scheduling_algorithm(Queue *job_queue)
{
    create_directory("./IO/output/SJF");
    FILE *algorithm_procedure_output_file = create_file("./IO/output/SJF/", "SJF - Algorithm Procedure", ".log");
    FILE *algorithm_analysis_output_file = create_file("./IO/output/SJF/", "SJF - Algorithm Analysis", ".log");
    FILE *processes_analysis_output_file = create_file("./IO/output/SJF/", "SJF - Processes Analysis", ".log");

    Queue *job_queue_copy = copy_queue(job_queue);
    ready_queue = create_new_queue(job_queue->capacity);
    running_process = NULL;
    waiting_queue = create_new_queue(job_queue->capacity);
    terminated_queue = create_new_queue(job_queue->capacity);

    int current_time = 0;

    fprintf(algorithm_procedure_output_file, "***Shortest Job First (SJF) or Shortest Process Next (SPN) Scheduling Algorithm in Operating System***\n\n");
    while (!is_full(terminated_queue))
    {
        fprintf(algorithm_procedure_output_file, "Time = %d-%d:\n", current_time, current_time + 1);

        if (!is_empty(job_queue) && front(job_queue)->arrival_time <= current_time)
        {
            enqueue(ready_queue, dequeue(job_queue));
            fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Job-Queue to Ready-Queue.\n", rear(ready_queue)->process_id);
        }

        if (!is_empty(ready_queue) && running_process == NULL)
        {
            running_process = remove_process_with_minimum_CPU_burst_time(ready_queue);
            if (running_process->response_time == -1)
                running_process->response_time = current_time;
            fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Ready-Queue to Running-State.\n", running_process->process_id);
        }

        if (!is_empty(waiting_queue))
        {
            front(waiting_queue)->IO_burst_time--;
            fprintf(algorithm_procedure_output_file, "\tProcess-%d's Waited for I/O Recourse for 1 Second (Remaining I/O Waiting Time = %d).\n", front(waiting_queue)->process_id, front(waiting_queue)->IO_burst_time);

            if (front(waiting_queue)->IO_burst_time == 0)
            {
                enqueue(ready_queue, dequeue(waiting_queue));
                fprintf(algorithm_procedure_output_file, "\tProcess-%d's IO's Waiting Time Was Finished and Was Moved From Waiting-Queue to Ready-Queue.\n", rear(ready_queue)->process_id);
            }
        }

        if (running_process != NULL)
            if (running_process->CPU_burst_time_1 == 0)
            {
                if (running_process->IO_burst_time == 0 && running_process->CPU_burst_time_2 != 0)
                {
                    running_process->CPU_burst_time_2--;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d's Second CPU Burst Was Executed for 1 Second (Remaining Second CPU Burst Time = %d).\n", running_process->process_id, running_process->CPU_burst_time_2);

                    if (running_process->CPU_burst_time_2 == 0)
                    {
                        enqueue(terminated_queue, running_process);
                        running_process->termination_time = current_time + 1;
                        running_process->turn_around_time = running_process->termination_time - running_process->arrival_time;
                        running_process->waiting_time = running_process->turn_around_time - (running_process->CPU_burst_time_1 + running_process->IO_burst_time + running_process->CPU_burst_time_2);
                        running_process = NULL;
                        fprintf(algorithm_procedure_output_file, "\tProcess-%d Was Terminated (Moved From Running-State to Terminated-Queue).\n", rear(terminated_queue)->process_id);
                    }
                }
            }
            else
            {
                running_process->CPU_burst_time_1--;
                fprintf(algorithm_procedure_output_file, "\tProcess-%d's First CPU Burst Was Executed for 1 Second (Remaining First CPU Burst Time = %d).\n", running_process->process_id, running_process->CPU_burst_time_1);

                if (running_process->CPU_burst_time_1 == 0 && running_process->IO_burst_time != 0)
                {
                    enqueue(waiting_queue, running_process);
                    running_process = NULL;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Running-State to Waiting-Queue to Execute It's IO Burst.\n", rear(waiting_queue)->process_id);
                }
            }

        current_time++;
    }

    fclose(algorithm_procedure_output_file);

    analyze_algorithm(job_queue_copy, terminated_queue, algorithm_analysis_output_file);
    analyze_processes(job_queue_copy, terminated_queue, processes_analysis_output_file);

    fclose(algorithm_analysis_output_file);
    fclose(processes_analysis_output_file);
}

// Shortest Remaining Time First (SRTF) Scheduling Algorithm in Operating Systems
void SRTF_scheduling_algorithm(Queue *job_queue)
{
    create_directory("./IO/output/SRTF");
    FILE *algorithm_procedure_output_file = create_file("./IO/output/SRTF/", "SRTF - Algorithm Procedure", ".log");
    FILE *algorithm_analysis_output_file = create_file("./IO/output/SRTF/", "SRTF - Algorithm Analysis", ".log");
    FILE *processes_analysis_output_file = create_file("./IO/output/SRTF/", "SRTF - Processes Analysis", ".log");

    Queue *job_queue_copy = copy_queue(job_queue);
    ready_queue = create_new_queue(job_queue->capacity);
    running_process = NULL;
    waiting_queue = create_new_queue(job_queue->capacity);
    terminated_queue = create_new_queue(job_queue->capacity);

    int current_time = 0;

    fprintf(algorithm_procedure_output_file, "***Shortest Remaining Time First (SRTF) Scheduling Algorithm in Operating System***\n\n");
    while (!is_full(terminated_queue))
    {
        fprintf(algorithm_procedure_output_file, "Time = %d-%d:\n", current_time, current_time + 1);

        if (!is_empty(job_queue) && front(job_queue)->arrival_time <= current_time)
        {
            enqueue(ready_queue, dequeue(job_queue));
            fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Job-Queue to Ready-Queue.\n", rear(ready_queue)->process_id);
        }

        if (!is_empty(ready_queue) && running_process == NULL)
        {
            running_process = remove_process_with_minimum_CPU_burst_time(ready_queue);
            if (running_process->response_time == -1)
                running_process->response_time = current_time;
            fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Ready-Queue to Running-State.\n", running_process->process_id);
        }

        if (!is_empty(waiting_queue))
        {
            front(waiting_queue)->IO_burst_time--;
            fprintf(algorithm_procedure_output_file, "\tProcess-%d's Waited for I/O Recourse for 1 Second (Remaining I/O Waiting Time = %d).\n", front(waiting_queue)->process_id, front(waiting_queue)->IO_burst_time);

            if (front(waiting_queue)->IO_burst_time == 0)
            {
                enqueue(ready_queue, dequeue(waiting_queue));
                fprintf(algorithm_procedure_output_file, "\tProcess-%d's IO's Waiting Time Was Finished and Was Moved From Waiting-Queue to Ready-Queue.\n", rear(ready_queue)->process_id);
            }
        }

        if (running_process != NULL)
            if (running_process->CPU_burst_time_1 == 0)
            {
                if (running_process->IO_burst_time == 0 && running_process->CPU_burst_time_2 != 0)
                {
                    running_process->CPU_burst_time_2--;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d's Second CPU Burst Was Executed for 1 Second (Remaining Second CPU Burst Time = %d).\n", running_process->process_id, running_process->CPU_burst_time_2);

                    if (running_process->CPU_burst_time_2 == 0)
                    {
                        enqueue(terminated_queue, running_process);
                        running_process->termination_time = current_time + 1;
                        running_process->turn_around_time = running_process->termination_time - running_process->arrival_time;
                        running_process->waiting_time = running_process->turn_around_time - (running_process->CPU_burst_time_1 + running_process->IO_burst_time + running_process->CPU_burst_time_2);
                        running_process = NULL;
                        fprintf(algorithm_procedure_output_file, "\tProcess-%d Was Terminated (Moved From Running-State to Terminated-Queue).\n", rear(terminated_queue)->process_id);
                    }
                    else
                    {
                        enqueue(ready_queue, running_process);
                        running_process = NULL;
                        fprintf(algorithm_procedure_output_file, "\tProcess-%d Was Preempted (Moved From Running-State to Ready-Queue).\n", rear(ready_queue)->process_id);
                    }
                }
            }
            else
            {
                // Decrease the CPU burst time of the process in the running queue by 1
                running_process->CPU_burst_time_1--;
                fprintf(algorithm_procedure_output_file, "\tProcess-%d's First CPU Burst Was Executed for 1 Second (Remaining First CPU Burst Time = %d).\n", running_process->process_id, running_process->CPU_burst_time_1);

                if (running_process->CPU_burst_time_1 == 0 && running_process->IO_burst_time != 0)
                {
                    enqueue(waiting_queue, running_process);
                    running_process = NULL;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Running-State to Waiting-Queue to Execute It's IO Burst.\n", rear(waiting_queue)->process_id);
                }
                else
                {
                    enqueue(ready_queue, running_process);
                    running_process = NULL;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d Was Preempted (Moved From Running-State to Ready-Queue).\n", rear(ready_queue)->process_id);
                }
            }

        current_time++;
    }

    fclose(algorithm_procedure_output_file);

    analyze_algorithm(job_queue_copy, terminated_queue, algorithm_analysis_output_file);
    analyze_processes(job_queue_copy, terminated_queue, processes_analysis_output_file);

    fclose(algorithm_analysis_output_file);
    fclose(processes_analysis_output_file);
}

// Multi-Level Feedback Queue (MLFQ) Scheduling Algorithm in Operating Systems
void MLFQ_scheduling_algorithm(Queue *job_queue)
{
    create_directory("./IO/output/MLFQ");
    FILE *algorithm_procedure_output_file = create_file("./IO/output/MLFQ/", "MLFQ - Algorithm Procedure", ".log");
    FILE *algorithm_analysis_output_file = create_file("./IO/output/MLFQ/", "MLFQ - Algorithm Analysis", ".log");
    FILE *processes_analysis_output_file = create_file("./IO/output/MLFQ/", "MLFQ - Processes Analysis", ".log");

    Queue *job_queue_copy = copy_queue(job_queue);
    ready_queue = create_new_queue(job_queue->capacity);
    Queue *ready_queue_level_2 = create_new_queue(job_queue->capacity);
    Queue *ready_queue_level_3 = create_new_queue(job_queue->capacity);
    running_process = NULL;
    waiting_queue = create_new_queue(job_queue->capacity);
    terminated_queue = create_new_queue(job_queue->capacity);

    int current_time = 0;
    int running_elapsed_time = 0;
    int running_process_previous_level = 1;

    fprintf(algorithm_procedure_output_file, "***Multi-Level Feedback Queue (MLFQ) Scheduling Algorithm in Operating System***\n\n");

    int time_quantum_level_1;
    printf("Enter Time Quantum for Level 1 Queue of Multi-Level Feedback Queue (MLFQ): ");
    scanf("%d", &time_quantum_level_1);
    int time_quantum_level_2;
    printf("Enter Time Quantum for Level 2 Queue of Multi-Level Feedback Queue (MLFQ): ");
    scanf("%d", &time_quantum_level_2);

    while (!is_full(terminated_queue))
    {
        fprintf(algorithm_procedure_output_file, "Time = %d-%d:\n", current_time, current_time + 1);

        if (!is_empty(job_queue) && front(job_queue)->arrival_time <= current_time)
        {
            enqueue(ready_queue, dequeue(job_queue));
            fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Job-Queue to Ready-Queue Level 1.\n", rear(ready_queue)->process_id);
        }

        if (!is_empty(ready_queue) && running_process == NULL)
        {
            running_process = dequeue(ready_queue);
            running_process_previous_level = 1;
            running_elapsed_time = 0;
            if (running_process->response_time == -1)
                running_process->response_time = current_time;
            fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Ready-Queue Level 1 to Running-State.\n", running_process->process_id);
        }
        else if (!is_empty(ready_queue_level_2) && running_process == NULL)
        {
            running_process = dequeue(ready_queue_level_2);
            running_process_previous_level = 2;
            running_elapsed_time = 0;
            if (running_process->response_time == -1)
                running_process->response_time = current_time;
            fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Ready-Queue Level 2 to Running-State.\n", running_process->process_id);
        }
        else if (!is_empty(ready_queue_level_3) && running_process == NULL)
        {
            running_process = dequeue(ready_queue_level_3);
            running_process_previous_level = 3;
            running_elapsed_time = 0;
            if (running_process->response_time == -1)
                running_process->response_time = current_time;
            fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Ready-Queue Level 3 to Running-State.\n", running_process->process_id);
        }

        if (!is_empty(waiting_queue))
        {
            front(waiting_queue)->IO_burst_time--;
            fprintf(algorithm_procedure_output_file, "\tProcess-%d's Waited for I/O Recourse for 1 Second (Remaining I/O Waiting Time = %d).\n", front(waiting_queue)->process_id, front(waiting_queue)->IO_burst_time);

            if (front(waiting_queue)->IO_burst_time == 0)
            {
                enqueue(ready_queue, dequeue(waiting_queue));
                fprintf(algorithm_procedure_output_file, "\tProcess-%d's IO's Waiting Time Was Finished and Was Moved From Waiting-Queue to Ready-Queue.\n", rear(ready_queue)->process_id);
            }
        }

        if (running_process != NULL)
            if (running_process->CPU_burst_time_1 == 0)
            {
                if (running_process->IO_burst_time == 0 && running_process->CPU_burst_time_2 != 0)
                {
                    running_process->CPU_burst_time_2--;
                    running_elapsed_time++;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d's Second CPU Burst Was Executed for 1 Second (Remaining Second CPU Burst Time = %d).\n", running_process->process_id, running_process->CPU_burst_time_2);

                    if (running_process->CPU_burst_time_2 == 0)
                    {
                        enqueue(terminated_queue, running_process);
                        running_process->termination_time = current_time + 1;
                        running_process->turn_around_time = running_process->termination_time - running_process->arrival_time;
                        running_process->waiting_time = running_process->turn_around_time - (running_process->CPU_burst_time_1 + running_process->IO_burst_time + running_process->CPU_burst_time_2);
                        running_process = NULL;
                        fprintf(algorithm_procedure_output_file, "\tProcess-%d Was Terminated (Moved From Running-State to Terminated-Queue).\n", rear(terminated_queue)->process_id);
                    }
                    else if (running_process_previous_level == 1 && running_elapsed_time == time_quantum_level_1)
                    {
                        enqueue(ready_queue_level_2, running_process);
                        running_process = NULL;
                        fprintf(algorithm_procedure_output_file, "\tProcess-%d Was Preempted (Moved From Running-State to Ready-Queue Level 2).\n", rear(ready_queue_level_2)->process_id);
                    }
                    else if (running_process_previous_level == 2 && running_elapsed_time == time_quantum_level_2)
                    {
                        enqueue(ready_queue_level_3, running_process);
                        running_elapsed_time = 0;
                        fprintf(algorithm_procedure_output_file, "\tProcess-%d Was Preempted (Moved From Running-State to Ready-Queue Level 3).\n", rear(ready_queue_level_3)->process_id);
                    }
                }
            }
            else
            {
                // Decrease the CPU burst time of the process in the running queue by 1
                running_process->CPU_burst_time_1--;
                running_elapsed_time++;
                fprintf(algorithm_procedure_output_file, "\tProcess-%d's First CPU Burst Was Executed for 1 Second (Remaining First CPU Burst Time = %d).\n", running_process->process_id, running_process->CPU_burst_time_1);

                if (running_process->CPU_burst_time_1 == 0 && running_process->IO_burst_time != 0)
                {
                    enqueue(waiting_queue, running_process);
                    running_process = NULL;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d Moved From Running-State to Waiting-Queue to Execute It's IO Burst.\n", rear(waiting_queue)->process_id);
                }
                else if (running_process_previous_level == 1 && running_elapsed_time == time_quantum_level_1)
                {
                    enqueue(ready_queue_level_2, running_process);
                    running_process = NULL;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d Was Preempted (Moved From Running-State to Ready-Queue Level 2).\n", rear(ready_queue_level_2)->process_id);
                }
                else if (running_process_previous_level == 2 && running_elapsed_time == time_quantum_level_2)
                {
                    enqueue(ready_queue_level_3, running_process);
                    running_process = NULL;
                    fprintf(algorithm_procedure_output_file, "\tProcess-%d Was Preempted (Moved From Running-State to Ready-Queue Level 3).\n", rear(ready_queue_level_3)->process_id);
                }
            }

        current_time++;
    }

    fclose(algorithm_procedure_output_file);

    analyze_algorithm(job_queue_copy, terminated_queue, algorithm_analysis_output_file);
    analyze_processes(job_queue_copy, terminated_queue, processes_analysis_output_file);

    fclose(algorithm_analysis_output_file);
    fclose(processes_analysis_output_file);
}