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
    char p_name;    // process name 
    int ariv_t;     // arrival time
    int rema_t;     // remain time
    int serv_t;     // service time
    int turn_t;     // turnaround time
    int resp_t;     // response time
    int qlevel;     // queue level(=priority)
    int ticket;     // ticket num
} Process;

/* Ready queue structure*/
typedef struct{
    Process **array; // queue buffer
    int size;       // queue size
    int count;      // count on ready process
    int front;      // front index of queue
	int rear;       // rear index of queue
} ReadyQueue;

/* Global variables */
extern int proc_num;        // number of process
extern int total_time;      // total execution time
Process task[MAX_PROC_NUM]; // task arrays
ReadyQueue *q;              // ready queue

/* lab1_ready_q.c : Ready Queue functions*/
ReadyQueue *initReadyQueue(unsigned size);
void enqueue(ReadyQueue * queue, Process *item);
Process *dequeue(ReadyQueue * queue);
Process *getFront(ReadyQueue * queue);
void printQueue(ReadyQueue * queue);

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
