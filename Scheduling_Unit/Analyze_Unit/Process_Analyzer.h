// Turnaround time = termination time - arrival time
int get_process_turnaround_time(Process *process)
{
    return process->termination_time - process->arrival_time;
}

// Waiting time = turnaround time - (CPU burst time 1 + IO burst time + CPU burst time 2)
int get_process_waiting_time(Process *process, Queue *job_queue)
{
    return get_process_turnaround_time(process) - (get_process_from_queue(process, job_queue)->CPU_burst_time_1 + get_process_from_queue(process, job_queue)->IO_burst_time + get_process_from_queue(process, job_queue)->CPU_burst_time_2);
}

// Analyze processes after scheduling
void analyze_processes(Queue *job_queue, Queue *terminated_queue, FILE *output_file)
{
    for (int i = 0; i < terminated_queue->size; i++)
    {
        fprintf(output_file, "Process %d:\n", terminated_queue->array[i]->process_id);
        fprintf(output_file, "\tarrival time: %d\n", terminated_queue->array[i]->arrival_time);
        fprintf(output_file, "\ttermination time: %d\n", terminated_queue->array[i]->termination_time);
        fprintf(output_file, "\tresponse time: %d\n", terminated_queue->array[i]->response_time);
        fprintf(output_file, "\tturnaround time: %d\n", get_process_turnaround_time(terminated_queue->array[i]));
        fprintf(output_file, "\twaiting time: %d\n", get_process_waiting_time(terminated_queue->array[i], job_queue));
    }
}