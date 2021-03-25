/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 
*	    Student name : 
*
*   lab1_io.c :
*       - Lab1 Ready queue function implementations
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

#include <limits.h>
#include "lab1_sched_types.h"

ReadyQueue *initReadyQueue(unsigned size){
	ReadyQueue *temp = (ReadyQueue *)malloc(sizeof(ReadyQueue));
	temp->rear = size-1;
	temp->front = size-1;
    temp->count = 0;
	temp->size = size;
	temp->array = (Process **)malloc(size * sizeof(Process *));
	return temp;
}

void enqueue(ReadyQueue * queue, Process *item){
	queue->rear = (queue->rear + 1) % queue->size;
	if(queue->rear == queue->front){
		queue->rear--;
	}else{
		queue->array[queue->rear] = item;	
	}
    queue->count++;
}

Process *dequeue(ReadyQueue * queue){
	if(queue->front == queue->rear ){
		return NULL;
	}
	queue->front = (queue->front + 1) % queue->size;
    queue->count--;
	return queue->array[queue->front];
}

Process *getFront(ReadyQueue * queue) {
    int i = (queue->front + 1) % queue->size;
    return queue->array[i];
}

void printQueue(ReadyQueue * queue) {
    printf("Queue : ");
    for (int i = 0; i < queue->size; i++)
    {
        printf("%c ", queue->array[queue->front+i]->p_name);
    }
}