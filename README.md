<h1 align="center">Operating System CPU-Scheduling Algorithms</h1>

# 1. First Come, First Serve (FCFS):
  - Definition:
  
    The first come first serve scheduling algorithm states that the process that requests the CPU first is allocated the CPU first and is implemented by using a FIFO queue.
  - Advantages:
    
    * Easy to implement
    * First come, first serve method
    
  - Disadvantages:
    
    * FCFS suffers from the Convoy effect.
    * The average waiting time is much higher than the other algorithms.
    * FCFS is very simple and easy to implement and hence not much efficient.
# 2. Round Robin (RR)
  - Definition:
  
    Round Robin is a CPU scheduling algorithm where each process is cyclically assigned a fixed time slot. It is the preemptive version of the First come First Serve CPU Scheduling algorithm. Round Robin CPU Algorithm generally focuses on Time Sharing technique. 

  - Characteristics:
  
    * It’s simple, easy to use, and starvation-free as all processes get the balanced CPU allocation.
    * One of the most widely used methods in CPU scheduling as a core.
    * It is considered preemptive as the processes are given to the CPU for a very limited time.
    
  - Advantages: 
  
    * Round robin seems to be fair as every process gets an equal share of CPU.
    * The newly created process is added to the end of the ready queue.
# 3. Shortest Job First (SJF)
  - Definition:
  
    Shortest job first (SJF) is a scheduling process that selects the waiting process with the smallest execution time to execute next. Significantly reduces the average waiting time for other processes waiting to be executed. The full form of SJF is Shortest Job First.

  - Characteristics:
  
    * Shortest Job first has the advantage of having a minimum average waiting time among all operating system scheduling algorithms.
    * It is associated with each task as a unit of time to complete.
    * It may cause starvation if shorter processes keep coming. This problem can be solved using the concept of aging.

  - Advantages:
  
    * As SJF reduces the average waiting time thus, it is better than the first come first serve scheduling algorithm.
    * SJF is generally used for long-term scheduling
    
  - Disadvantages:
  
    * One of the demerits SJF has is starvation.
    * Many times it becomes complicated to predict the length of the upcoming CPU request

# 4. Shortest Remaining-Time First (STRF)
  - Definition:
  
    The shortest remaining time first is the preemptive version of the Shortest job first which we have discussed earlier where the processor is allocated to the job closest to completion. In SRTF the process with the smallest amount of time remaining until completion is selected to execute.

  - Characteristics:
  
    * SRTF algorithm makes the processing of the jobs faster than the SJF algorithm, given its overhead charges are not counted. 
    * The context switch is done a lot more times in SRTF than in SJF and consumes the CPU’s valuable time for processing. This adds up to its processing time and diminishes its advantage of fast processing.
    
  - Advantages:
    
    * In SRTF the short processes are handled very fast.
    * The system also requires very little overhead since it only makes a decision when a process completes or a new process is added. 

  - Disadvantages:

    * Like the shortest job first, it also has the potential for process starvation. 
    * Long processes may be held off indefinitely if short processes are continually added. 
    
# 5. Multi-Level Feedback Queue (MLFQ)
  - Definition:
  
    Multilevel Feedback Queue Scheduling (MLFQ) CPU Scheduling is like  Multilevel Queue Scheduling but in this process can move between the queues. And thus, much more efficient than multilevel queue scheduling. 

  - Characteristics:
  
    * In a multilevel queue-scheduling algorithm, processes are permanently assigned to a queue on entry to the system, and processes are not allowed to move between queues. 
    * As the processes are permanently assigned to the queue, this setup has the advantage of low scheduling overhead, 
    * But on the other hand disadvantage of being inflexible.

  - Advantages:
  
    * It is more flexible
    * It allows different processes to move between different queues

  - Disadvantages:
  
    * It also produces CPU overheads
    * It is the most complex algorithm.
    
<h1 align="center">Processes Analyser</h1>

## 1. Arrival Time/ Creation Time

  - The Time Which the Process is Added To the Job Queue
  - Given in the Input
  
## 2. Termination Time/ Completion Time

  - The Time Which the Proces Completes It's Excutoin and Is Added to the Terminated Queue
  
## 3. Response Time

  - In a collaborative system, turn around time is not the best option. The process may produce something early and continue to computing the new results while the previous results are released to the user. Therefore another method is the time taken in the submission of the application process until the first response is issued. This measure is called response time.
  - The First Time Which the Process is Moved to Running State.
  
## 4. Turnaround Time
 
  - For a particular process, the important conditions are how long it takes to perform that process. The time elapsed from the time of process delivery to the time of completion is known as the conversion time. Conversion time is the amount of time spent waiting for memory access, waiting in line, using CPU, and waiting for I / O.
 - Terminatoin Time - Arrivial Time
  
## 5. Waiting Time

  - The Scheduling algorithm does not affect the time required to complete the process once it has started performing. It only affects the waiting time of the process i.e. the time spent in the waiting process in the ready queue.
  - Turnaround Time - (CPU Burst Time + IO Birst Time)
  
  <h1 align="center">Algorithms Analyser</h1>
  
  ## 1. CPU Execution Time/ CPU Active Time
  ## 2. CPU idle time
  ## 3. CPU Utilization
  
  - The main purpose of any CPU algorithm is to keep the CPU as busy as possible. Theoretically, CPU usage can range from 0 to 100 but in a real-time system, it varies from 40 to 90 percent depending on the system load.
    
  ## 4. Throughput
  
  - The average CPU performance is the number of processes performed and completed during each unit. This is called throughput. The output may vary depending on the length or duration of the processes.

  ## 5. Average turnaround time
  ## 6. Average waiting time
  ## 7. Average response time
