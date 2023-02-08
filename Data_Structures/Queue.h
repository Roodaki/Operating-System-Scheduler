#include "process.h"

// Standard Queue Structure
typedef struct queue
{
    int front, rear, size;
    unsigned capacity;
    Process **array;
} Queue;

// Create a new queue with given capacity and return the queue
Queue *create_new_queue(unsigned capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (Process **)malloc(queue->capacity * sizeof(Process *));

    return queue;
}

// Check if the queue is full
int is_full(Queue *queue)
{
    return queue->size == queue->capacity;
}

// Check if the queue is empty
int is_empty(Queue *queue)
{
    return queue->size == 0;
}

// Add a process to the queue
void enqueue(Queue *queue, Process *process)
{
    if (is_full(queue))
        return;

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = process;
    queue->size++;
}

// Remove a process from the queue
Process *dequeue(Queue *queue)
{
    if (is_empty(queue))
        return NULL;

    Process *process = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return process;
}

// Get the front process of the queue
Process *front(Queue *queue)
{
    if (is_empty(queue))
        return NULL;

    return queue->array[queue->front];
}

// Get the rear process of the queue
Process *rear(Queue *queue)
{
    if (is_empty(queue))
        return NULL;

    return queue->array[queue->rear];
}

// Sort the queue according to the arrival time of the processes
void sort_queue(Queue *queue)
{
    for (int i = 0; i < queue->size - 1; i++)
        for (int j = 0; j < queue->size - i - 1; j++)
            if (queue->array[j]->arrival_time > queue->array[j + 1]->arrival_time)
            {
                Process *temp = queue->array[j];
                queue->array[j] = queue->array[j + 1];
                queue->array[j + 1] = temp;
            }
}

// Print all processes in the queue and their attributes
void print_queue(Queue *queue)
{
    puts("\nProcesses in the queue:");
    for (int i = 0; i < queue->size; i++)
        print_process(queue->array[i]);
}

// Copy a queue and return the new queue
Queue *copy_queue(Queue *queue)
{
    Queue *new_queue = create_new_queue(queue->capacity);
    for (int i = 0; i < queue->size; i++)
        enqueue(new_queue, copy_process(queue->array[i]));
    return new_queue;
}

// Return a process from a given queue with the given process id or NULL if not found
Process *get_process_from_queue(Process *process, Queue *queue)
{
    for (int i = 0; i < queue->size; i++)
        if (queue->array[i]->process_id == process->process_id)
            return queue->array[i];
    return NULL;
}

// Physically remove a process from the queue
void remove_process(Queue *queue, Process *process)
{
    for (int i = 0; i < queue->size; i++)
        if (queue->array[i] == process)
        {
            for (int j = i; j < queue->size - 1; j++)
                queue->array[j] = queue->array[j + 1];
            queue->size--;
            break;
        }
    queue->rear--;
}

// Return the process with minimum CPU burst time
Process *get_process_with_minimum_CPU_burst_time(Queue *queue)
{
    Process *process = queue->array[0];
    for (int i = 1; i < queue->size; i++)
        if (((process->CPU_burst_time_1 != 0 && queue->array[i]->CPU_burst_time_1 != 0) && queue->array[i]->CPU_burst_time_1 < process->CPU_burst_time_1) ||
            ((process->CPU_burst_time_1 == 0 && queue->array[i]->CPU_burst_time_1 != 0) && queue->array[i]->CPU_burst_time_1 < process->CPU_burst_time_2) ||
            ((process->CPU_burst_time_1 != 0 && queue->array[i]->CPU_burst_time_1 == 0) && queue->array[i]->CPU_burst_time_2 < process->CPU_burst_time_1) ||
            ((process->CPU_burst_time_1 == 0 && queue->array[i]->CPU_burst_time_1 == 0)) && queue->array[i]->CPU_burst_time_2 < process->CPU_burst_time_2)
            process = queue->array[i];
    return process;
}

// Return the process with minimum CPU burst time and remove it from the queue
Process *remove_process_with_minimum_CPU_burst_time(Queue *queue)
{
    Process *process = get_process_with_minimum_CPU_burst_time(queue);
    remove_process(queue, process);
    return process;
}