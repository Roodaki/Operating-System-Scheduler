<div align="center">
  <h1><strong>Operating-System Scheduler</strong></h1>
  <p><strong>This project aims to provide a comprehensive simulation of the scheduling procedures employed by operating systems. By implementing various scheduling algorithms, this project enables users to analyze and evaluate their performance in different scenarios. It aims to facilitate a deeper understanding of scheduling concepts and assist in comparing the effectiveness of different algorithms.</strong></p>
</div>

## Table of Contents
- [Features](#features)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Requirements](#requirements)
  - [Installation](#installation)
  - [Usage Guide](#usage-guide)
- [Example](#example)

## Features
- Implement the following scheduling algorithms:
  - First-Come, First-Served (FCFS)
  - Shortest Job First (SJF)
  - Round Robin (RR)
  - Shortest Remaining Time First (SRTF)
  - Multilevel Feedback Queue (MLFQ)
- Simulate scheduling processes based on the implemented algorithms by generating detailed time-line logs to track process movements.
- Utilize the following states in the scheduling procedure:
  - New
  - Ready
  - Running
  - Waiting
  - Terminated
- Analyze the performance of scheduling algorithms using the following measurements:
  - CPU Utilization
  - Throughput
  - Average Turnaround Time
  - Average Waiting Time
  - Average Response Time

## Project Structure
The project has the following structure:
```
├── Data Structures/
│   ├── process.h
│   └── queue.h
├── IO/
│   ├── input/
│   │   └── input_processes.csv
│   ├── output/
│   └── user_interactions_unit.h
├── Scheduling_Unit/
│   ├── scheduler.h
│   └── Analyze_Unit/
│       ├── algorithm_analyzer.h
│       └── process_analyzer.h
├── main.c
├── .gitignore
└── README.md
```

## Getting Started
### Requirements
* C compiler (e.g., GCC)
* Git command line tool (or Git GUI client) to clone the repository.
### Installation
1. Open a terminal or command prompt.
2. Clone this repository: `git clone https://github.com/Roodaki/Operating-System-Scheduler`
3. Navigate to the cloned repository's directory and Compile the source code using the following command: `gcc main.c -o scheduler`
4. Run the compiled executable: `./scheduler`
### Usage Guide
1. Prepare a CSV file containing the processes of the job queue in the following format: 
    ```
    process_id,arrival_time,cpu_time1,io_time,cpu_time2
    ```
    - **process_id**: Unique identifier for the process.
    - **arrival_time**: The time at which the process arrives in the system.
    - **cpu_time1**: The duration of the first CPU burst time for the process.
    - **io_time**: The duration of I/O burst time for the process.
    - **cpu_time2**: The duration of the second CPU burst time for the process.
2. Compile and run the program.
3. After the execution is completed, you will find the output in the following structure:
    ```
    └── output
        ├── FCFS
        │   ├── FCFS - Algorithm Analysis.log
        │   ├── FCFS - Algorithm Procedure.log
        │   └── FCFS - Processes Analysis.log
        ├── SJF
        │   ├── SJF - Algorithm Analysis.log
        │   ├── SJF - Algorithm Procedure.log
        │   └── SJF - Processes Analysis.log
        ├── RR
        │   ├── RR - Algorithm Analysis.log
        │   ├── RR - Algorithm Procedure.log
        │   └── RR - Processes Analysis.log
        ├── SRTF
        │   ├── SRTF - Algorithm Analysis.log
        │   ├── SRTF - Algorithm Procedure.log
        │   └── SRTF - Processes Analysis.log
        └── MLFQ
            ├── MLFQ - Algorithm Analysis.log
            ├── MLFQ - Algorithm Procedure.log
            └── MLFQ - Processes Analysis.log
    ```
    - For each algorithm, there will be a separate folder created in the output directory.
    - Inside each algorithm folder, you will find three log files:
        - **algorithm_procedure.log**: This file contains the time-line of the algorithm, detailing the movements of the processes during the scheduling.
        - **algorithm_analysis.log**: This file contains the calculated measurements of the algorithm, such as CPU utilization, throughput, average turnaround time, average waiting time, and average response time.
        - **process_analysis.log**: This file contains the calculated measurements for each individual process, including its turnaround time, waiting time, and response time.

## Example
Assuming you have entered following process to the "input_process.csv" file:
```
process_id,arrival_time,cpu_time1,io_time,cpu_time2
1,0,4,4,1
2,2,1,1,3
```
The "output" directory contains separate directories for each scheduling algorithm: FCFS, SJF, RR, SRTF, and MLFQ. Within each algorithm directory, there are specific log files related to algorithm analysis, algorithm procedure, and process analysis.
### RR - Algorithm Analysis.log:
```
CPU execution time: 9
CPU idle time: 3
CPU utilization: 75.00%
Throughput: 6.00
Average turnaround time: 9.50
Average waiting time: 2.50
Average response time: 2.00
```
### RR - Algorithm Procedure.log:
```
Time = 0-1:
Process-1 moves from the Job Queue to the Ready Queue.
Process-1 moves from the Ready Queue to the Running State.
Process-1's first CPU burst is executed for 1 second (Remaining first CPU burst time = 3).
Time = 1-2:
Process-1's first CPU burst is executed for 1 second (Remaining first CPU burst time = 2).
Process-1's time quantum is finished and it moves from the Running State to the Ready Queue.
Time = 2-3:
Process-2 moves from the Job Queue to the Ready Queue.
Process-1 moves from the Ready Queue to the Running State.
Process-1's first CPU burst is executed for 1 second (Remaining first CPU burst time = 1).
Time = 3-4:
Process-1's first CPU burst is executed for 1 second (Remaining first CPU burst time = 0).
Process-1 moves from the Running State to the Waiting Queue to execute its I/O burst.
Time = 4-5:
Process-2 moves from the Ready Queue to the Running State.
Process-1 waits for I/O resource for 1 second (Remaining I/O waiting time = 3).
Process-2's first CPU burst is executed for 1 second (Remaining first CPU burst time = 0).
Process-2 moves from the Running State to the Waiting Queue to execute its I/O burst.
Time = 5-6:
Process-1 waits for I/O resource for 1 second (Remaining I/O waiting time = 2).
Time = 6-7:
Process-1 waits for I/O resource for 1 second (Remaining I/O waiting time = 1).
Time = 7-8:
Process-1 waits for I/O resource for 1 second (Remaining I/O waiting time = 0).
Process-1's I/O waiting time is finished and it moves from the Waiting Queue to the Ready Queue.
Time = 8-9:
Process-1 moves from the Ready Queue to the Running State.
Process-2 waits for I/O resource for 1 second (Remaining I/O waiting time = 0).
Process-2's I/O waiting time is finished and it moves from the Waiting Queue to the Ready Queue.
Process-1's second CPU burst is executed for 1 second (Remaining second CPU burst time = 0).
Process-1 is terminated (moved from the Running State to the Terminated Queue).
Time = 9-10:
Process-2 moves from the Ready Queue to the Running State.
Process-2's second CPU burst is executed for 1 second (Remaining second CPU burst time = 2).
Time = 10-11:
Process-2's second CPU burst is executed for 1 second (Remaining second CPU burst time = 1).
Time = 11-12:
Process-2's second CPU burst is executed for 1 second (Remaining second CPU burst time = 0).
Process-2 is terminated (moved from the Running State to the Terminated Queue).
```
### RR - Processes Analysis.log:
```
Process-1:
Turnaround Time: 9
Waiting Time: 4
Response Time: 2

Process-2:
Turnaround Time: 10
Waiting Time: 4
Response Time: 3
```
You can find similar log files for each scheduling algorithm to analyze their respective performance and understand the process movements throughout the simulation.
