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

#include "sched_types.h"

int main(int argc, char *argv[]){

    fcfs();
    spn();
    rr(1);
    rr(4);
    mlfq_1();
    mlfq_2();
    lott();
}

