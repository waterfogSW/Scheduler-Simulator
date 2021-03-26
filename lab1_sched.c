/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32170578
*	    Student name : 김산
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

    printf("fcfs        : ");
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
        output[cpu_time] = cur->p_name;
        while (next_idx < proc_num && task[next_idx].ariv_t == cpu_time) {
            enqueue(&task[next_idx++]);
        }
        sortbyServ();
        run(cur);
        if(cur->rema_t == 0) {
            cur = dequeue();
        }
        cpu_time++;
    }
    printf("spn         : ");
    printOutput(output);
    fin();
}

void rr(int q) {
    init();
    char output[total_time];
    int next_idx = 0;
    int cpu_time = 0;
    int flag = 0;
    Process *cur= &task[next_idx++];
    Process *tmp;
    setTimeQ(q);

    while (cpu_time < total_time) {
        while (next_idx < proc_num && task[next_idx].ariv_t == cpu_time) {
            enqueue(&task[next_idx++]);
        }
        if(flag == 1) {
            enqueue(tmp);
            cur = dequeue();
            flag = 0;
        }
        output[cpu_time] = cur->p_name;
        run(cur);
        if(cur->rema_t <= 0) {
            cur = dequeue();
        } else if(cur->time_q <= 0) {
            tmp = cur;
            tmp->time_q = q;
            flag = 1;
        }
        cpu_time++;
    }
    printf("rr(q=%d)     : ", q);
    printOutput(output);
    fin();
}

void mlfq_1() {
    init();
    char output[total_time];
    int next_idx = 0;
    int cpu_time = 0;
    int flag = 0;
    Process *cur= &task[next_idx++];
    Process *tmp;
    setTimeQ(1);

    while (cpu_time < total_time) {
        while (next_idx < proc_num && task[next_idx].ariv_t == cpu_time) {
            enqueue(&task[next_idx++]);
        }
        if(flag == 1) {
            if (rq.count != 0) {
                cur->qlevel++;
                cur->time_q = 1;
                tmp = cur;
                sortbylevel();
                cur = dequeue();
                enqueue(tmp);
            } else {
                cur->time_q = 1;
            }
        }
        output[cpu_time] = cur->p_name;
        run(cur);
        if(cur->rema_t == 0) {
            cur = dequeue();
        } else if (cur->time_q == 0) {
            flag = 1;
        }
        
        cpu_time++;
    }
    printf("mlfq(q=1)   : ");
    printOutput(output);
    fin();
}

void mlfq_2() {

}

void lott() {


}
