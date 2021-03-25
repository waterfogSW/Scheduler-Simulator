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
    initReadyQueue(10);
    enqueue(&task[0]);
    enqueue(&task[1]);
    enqueue(&task[2]);

    printQueue();
    // int next_idx = 0;
    // Process *sched_task = &task[next_idx++];
    // for (int time = 0; time < total_time; time++) {
    //     while(next_idx<proc_num && task[next_idx].ariv_t == time) {

    //     }
    // }
}

void spn() {
    init();
}

void rr(int q) {
    init();
}

void mlfq_1() {

}

void mlfq_2() {

}

void lott() {

}
