<h1 align="center">Operating System CPU-Scheduling Algorithms Implementation</h1>

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
