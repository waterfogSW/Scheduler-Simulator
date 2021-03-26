/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 
*	    Student name : 
*
*   lab1_io.c :
*       - Lab1 io function file.
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

char *output;

void printProcInfo(){
    for (int i = 0; i < proc_num; i++) {
        printf("%c : %d, %d \n",task[i].p_name, task[i].ariv_t,task[i].serv_t);
    }
    printf("Process num : %d\n", proc_num);
    printf("Total  time : %d\n", total_time);
}

void printOutput(){
    for (int i = 0; i < total_time; i++){
        printf("%c ", output[i]);
    }
}