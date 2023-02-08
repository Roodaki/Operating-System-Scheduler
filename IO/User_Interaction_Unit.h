#include "../Data_Structures/Queue.h"

// create a new file in a given directory with given name and given extension
FILE *create_file(char *path, char *name, char *extension)
{
    char file_path[100];
    strcpy(file_path, path);
    strcat(file_path, name);
    strcat(file_path, extension);

    FILE *file = fopen(file_path, "w");
    return file;
}

// create a directory if it doesn't exist already with given name in given path
void create_directory(char *path)
{
    mkdir(path, 0777);
}

//  Count the number of lines in a CSV file
int count_lines_in_CSV_file(char *path)
{
    FILE *CSV_file = fopen(path, "r");

    char line[1024];
    fgets(line, sizeof(line), CSV_file);

    int count = 0;
    while (fgets(line, sizeof(line), CSV_file))
        count++;

    fclose(CSV_file);

    return count;
}

// Read input Processes from CSV File and return a queue of processes to be scheduled
Queue *read_processes_from_CSV_file(char *path)
{
    FILE *CSV_file = fopen(path, "r");

    char line[1024];
    fgets(line, sizeof(line), CSV_file);

    unsigned int process_id, arrival_time, CPU_burst_time_1, IO_burst_time, CPU_burst_time_2;
    Queue *queue = create_new_queue(count_lines_in_CSV_file(path));
    while (fscanf(CSV_file, "%u,%u,%u,%u,%u", &process_id, &arrival_time, &CPU_burst_time_1, &IO_burst_time, &CPU_burst_time_2) != EOF)
        enqueue(queue, create_new_process(process_id, arrival_time, CPU_burst_time_1, IO_burst_time, CPU_burst_time_2));

    fclose(CSV_file);

    create_directory("./IO/output");

    return queue;
}