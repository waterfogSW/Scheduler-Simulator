/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 
*	    Student name : 
*
*   lab1_sched_types.h :
*       - lab1 header file.
*       - must contains scueduler algorithm function's declations.
*
*/

#ifndef _LAB1_HEADER_H
#define _LAB1_HEADER_H

#define Q_BUF 10                // Define buffer size of ready queue
#define MAX_PROC_NUM 10         // Define MAX process number
#define FILE_NAME "./input.txt" // Define parsing file name(path)

/* Process structure*/
typedef struct {
    char p_name;    // Process name 
    int ariv_t;     // Arrival time
    int rema_t;     // Remain time
    int serv_t;     // Service time
    int turn_t;     // Turnaround time
    int resp_t;     // Response time
    int qlevel;     // Queue level(=priority)
    int ticket;     // Ticket num
} Process;

/* Ready queue structure*/
typedef struct{
    Process **array;// Queue buffer
    int size;       // Queue size
    int count;      // Number of processes in the queue
    int front;      // Front index of queue
	int rear;       // Rear index of queue
} ReadyQueue;

/* Global variables */
extern int proc_num;        // number of process
extern int total_time;      // total execution time
Process task[MAX_PROC_NUM]; // task arrays
ReadyQueue rq;              // ready queue

/* lab1_ready_q.c : Ready Queue functions*/
void initReadyQueue(unsigned size);
void enqueue(Process *item);
Process *dequeue();
Process *getFront();
void printQueue();

/* lab1_init.c : Process initialize functions */
void init();            // initialize process
void parseInput();      // parse from input.txt file
void sortInput();       // sort task by arrival time
void setTotalTime();    // set Totaltime variable by sum of tasks service time

/* lab1_io.c : task io functions */
void printProcInfo();
void printOutput();

/* lab1_sched.c : Scheduler functions */
void fcfs();		// FCFS : first come first serve
void spn();		    // SPN  : shortest process next
void rr(int q);	    // RR   : round robin
void mlfq_1();		// MLFQ : multi level feedback queue (q = 1)
void mlfq_2();		// MLFQ : multi level feedback queue (q = 2^i)
void lott();	    // implement at lottery.c

#endif /* LAB1_HEADER_H*/
