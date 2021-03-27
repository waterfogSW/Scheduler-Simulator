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
        output[cpu_time++] = cur->p_name;
        run(cur);
        if(cur->rema_t == 0) {
            cur = dequeue();
        }
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
        output[cpu_time++] = cur->p_name;
        while (next_idx < proc_num && task[next_idx].ariv_t == cpu_time) {
            enqueue(&task[next_idx++]);
        }
        sortbyServ();
        run(cur);
        if(cur->rema_t == 0) {
            cur = dequeue();
        }
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
        output[cpu_time++] = cur->p_name;
        run(cur);
        if(cur->rema_t <= 0) {
            cur = dequeue();
        } else if(cur->time_q <= 0) {
            tmp = cur;
            tmp->time_q = q;
            flag = 1;
        }
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
    init();
    char output[total_time];
    int next_idx = 0;
    int cpu_time = 0;
    int flag = 0;
    Process *cur = &task[next_idx++];
    Process *tmp;
    setTimeQ(1);

    while (cpu_time < total_time) {
        while (next_idx < proc_num && task[next_idx].ariv_t == cpu_time) {
            enqueue(&task[next_idx++]);
        }
        cur->qlevel++;
        if(--cur->rema_t > 0) {
            enqueue(cur);
			sortbylevel();
        }
        cpu_time++;
    }
    printf("mlfq(q=2)   : ");
    printf("\n");
    fin();
}

void lott() {
    init();
    char output[total_time];
    int next_idx = 0;
    int cpu_time = 0;
    int complete = 0;

    Process *cur;
    enqueue(&task[0]);
    while(cpu_time < total_time) {
        while (next_idx < proc_num && task[next_idx].ariv_t == cpu_time) {
            enqueue(&task[next_idx++]);
        }
        cur = get_winner();
        run(cur);
        output[cpu_time++] = cur->p_name;
        if(cur->rema_t <= 0) del_data(cur);
    }
    printf("lottery     : ");
    printOutput(output);
    fin();
}

// A 0 Queue :         A 0 Queue : 
// A 0 Queue :         A 0 Queue :     
// B 0 Queue : A       B 0 Queue : A1 
// A 1 Queue : B       A 1 Queue : B1 
// C 0 Queue : B       C 0 Queue : B1    
// B 2 Queue : C       B 2 Queue : C1
// C 1 Queue : D B     D 0 Queue : C1 B2     
// D 0 Queue : B C     C 1 Queue : B2 D1     
// B 3 Queue : C E D   E 0 Queue : D1 B2 C2     
// C 2 Queue : E D B   D 1 Queue : C2 B2 E1     
// E 0 Queue : D B C   E 1 Queue : C2 B2 D2     
// D 1 Queue : B C E   D 2 Queue : B2 C2     
// B 4 Queue : C E D   B 3 Queue : C D             
// C 3 Queue : E D B   C 3 Queue : D B     
// D 2 Queue : B E     D 3 Queue : B C                     
// B 5 Queue : E D     B 4 Queue : C D 
// E 2 Queue : D B     C 4 Queue : D B     
// B 6 Queue : D       B 5 Queue : D         
// D 4 Queue :         D 5 Queue : B 
// D 4 Queue :         B 6 Queue :  
