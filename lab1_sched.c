/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 
*	    Student name : 
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm function'definition.
*
*/

#include <aio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>

#include "lab1_sched_types.h"

void fcfs() {
    init();
    char output[total_time];
    int next_idx = 0;
    int cpu_time = 0;

    Process *cur= &task[next_idx++];
    while (cpu_time < total_time) {
        while (next_idx < proc_num && task[next_idx].ariv_t == cpu_time) {
            enqueue(&task[next_idx++]);
        }
        output[cpu_time] = cur->p_name;
        run(cur);
        if(cur->rema_t == 0) {
            cur = dequeue();
        }
        cpu_time++;
    }

    printf("fcfs    : ");
    printOutput(output);
    fin();
}

void spn() {
    init();
    char output[total_time];
    int next_idx = 0;
    int cpu_time = 0;

    Process *cur= &task[next_idx++];
    while (cpu_time < total_time) {
        while (next_idx < proc_num && task[next_idx].ariv_t == cpu_time) {
            enqueue(&task[next_idx++]);
        }
        sortbyServ();
        output[cpu_time] = cur->p_name;
        run(cur);
        if(cur->rema_t == 0) {
            cur = dequeue();
        }
        cpu_time++;
    }

    printf("spn     : ");
    printOutput(output);
    fin();
}

void rr(int q) {
    init();
    char output[total_time];
    int next_idx = 0;
    int cpu_time = 0;
    
    while (cpu_time < total_time) {
        /* code */
    }
    

    fin();
}

void mlfq_1() {

}

void mlfq_2() {

}

void lott() {

}
