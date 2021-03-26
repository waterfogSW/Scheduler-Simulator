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

/* Sort ready queue by service time */
void sortbyServ() {
    Process *tmp;
    int serv_tmp1;
    int serv_tmp2;
    int *idx = (int*)malloc(sizeof(int)*rq.count);

    printf("count : %d | ",rq.count);
    for (int i = 0; i < rq.count; i++) {
        idx[i] = (rq.front + i + 1) % rq.size;
        printf("%d : %c %d |", i,rq.array[idx[i]]->p_name, rq.array[idx[i]]->serv_t);
    }
    printf("\n");
    

    // for (int i = rq.count - 1; i > 0; i++) {
    //     for (int j = 0; j < i; j++) {
    //         serv_tmp1 = rq.array[idx[j]]->serv_t;
    //         serv_tmp2 = rq.array[idx[j+1]]->serv_t;
    //         if(serv_tmp1 > serv_tmp2) {
    //             tmp = rq.array[idx[j]];
    //             rq.array[idx[j+1]] = rq.array[idx[j]];
    //             rq.array[idx[j]] = tmp;
    //         }
    //     }    
    // }
    free(idx);
}

void run(Process *run) {
    run->rema_t--;
}
