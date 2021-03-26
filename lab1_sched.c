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
    int complete = 0;
    int cpu_time = 0;

    Process *run= &task[next_idx++];

    while(complete < proc_num){
	// arrival time same service time than next task put queue
		while(next_idx<proc_num && task[next_idx].ariv_t == cpu_time){
			enqueue(&task[next_idx]);
			next_idx++;
		}
		printf("%c ",run->p_name);	// now process name print
		output[cpu_time] = run->p_name;	// store present process name put for print table

		cpu_time++;		// service time increament
		if(--run->rema_t <= 0){	// task kill and next task pop
			complete++;
			run->turn_t = cpu_time - run->ariv_t;
			run = dequeue();
		}
	}
    fin();
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
