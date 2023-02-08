#include "process_analyzer.h"

// finish_time = last process termination time
int get_finish_time(Queue *terminated_queue)
{
    int finish_time = terminated_queue->array[0]->termination_time;
    for (int i = 1; i < terminated_queue->size; i++)
        if (terminated_queue->array[i]->termination_time > finish_time)
            finish_time = terminated_queue->array[i]->termination_time;
    return finish_time;
}

// CPU_execution_time = sum of CPU burst times of all processes
int get_CPU_execution_time(Queue *job_queue)
{
    int CPU_execution_time = 0;
    for (int i = 0; i < job_queue->size; i++)
        CPU_execution_time += job_queue->array[i]->CPU_burst_time_1 + job_queue->array[i]->CPU_burst_time_2;
    return CPU_execution_time;
}

// CPU_utilization_percent = CPU_execution_time / finish_time * 100
float get_CPU_utilization_percent(Queue *job_queue, Queue *terminated_queue)
{
    return (float)get_CPU_execution_time(job_queue) / get_finish_time(terminated_queue) * 100;
}

// CPU_idle_time = finish_time - CPU_execution_time
int get_CPU_idle_time(Queue *job_queue, Queue *terminated_queue)
{
    return get_finish_time(terminated_queue) - get_CPU_execution_time(job_queue);
}

// throughput = finish_time / number of processes
float get_throughput(Queue *job_queue, Queue *terminated_queue)
{
    return get_finish_time(terminated_queue) / (float)terminated_queue->size;
}

// average_turnaround_time = sum of turnaround times of all processes / number of processes
float get_average_turnaround_time(Queue *terminated_queue)
{
    float average_turnaround_time = 0;
    for (int i = 0; i < terminated_queue->size; i++)
        average_turnaround_time += get_process_turnaround_time(terminated_queue->array[i]);
    return average_turnaround_time / terminated_queue->size;
}

// average_waiting_time = sum of waiting times of all processes / number of processes
float get_average_waiting_time(Queue *terminated_queue, Queue *job_queue)
{
    float average_waiting_time = 0;
    for (int i = 0; i < terminated_queue->size; i++)
        average_waiting_time += get_process_waiting_time(terminated_queue->array[i], job_queue);
    return average_waiting_time / terminated_queue->size;
}

// average_response_time = sum of response times of all processes / number of processes
float get_average_response_time(Queue *terminated_queue)
{
    float average_response_time = 0;
    for (int i = 0; i < terminated_queue->size; i++)
        average_response_time += terminated_queue->array[i]->response_time;
    return average_response_time / terminated_queue->size;
}

void analyze_algorithm(Queue *job_queue, Queue *terminated_queue, FILE *output_file)
{
    fprintf(output_file, "CPU execution time: %d\n", get_CPU_execution_time(job_queue));
    fprintf(output_file, "CPU idle time: %d\n", get_CPU_idle_time(job_queue, terminated_queue));
    fprintf(output_file, "CPU utilization: %.2f%%\n", get_CPU_utilization_percent(job_queue, terminated_queue));
    fprintf(output_file, "Throughput: %.2f\n", get_throughput(job_queue, terminated_queue));
    fprintf(output_file, "Average turnaround time: %.2f\n", get_average_turnaround_time(terminated_queue));
    fprintf(output_file, "Average waiting time: %.2f\n", get_average_waiting_time(terminated_queue, job_queue));
    fprintf(output_file, "Average response time: %.2f\n", get_average_response_time(terminated_queue));
}