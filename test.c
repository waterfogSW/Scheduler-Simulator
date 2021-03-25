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

#define Q_BUF 10                // Define buffer size of ready queue
#define MAX_PROC_NUM 10         // Define MAX process number
#define FILE_NAME "./input.txt" // Define parsing file name(path)

int proc_num = 0;
int total_time = 0;
char *output;

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
ReadyQueue rq;              // ready queue

/* Parse process information from input.txt file */
void parseInput () {
    FILE *fp;           // file pointer
    int line_num = 0;   // count number of line

    char pid_p;         // parsed process id
    int ariv_p;         // parsed arrival time
    int serv_p;         // parsed service time

    /* input.txt file open */
    if((fp = fopen(FILE_NAME,"r")) == NULL) {
        fprintf(stderr, "Fail to open file: \"%s\", errno:%d\n", FILE_NAME, errno);
        perror("open\n");
        return;
    }

    /* Read file, parse pid, arrival time and service time */
    while(!feof(fp)) {
        /* Parse element of each line */
        fscanf(fp, "%c %d %d\n", &pid_p, &ariv_p, &serv_p);

        /* Initialize process struct */
        task[line_num].p_name = pid_p;
        task[line_num].ariv_t = ariv_p;
        task[line_num].rema_t = ariv_p;
        task[line_num].serv_t = serv_p;
        task[line_num].turn_t = -1;
        task[line_num].resp_t = -1;
        task[line_num].qlevel = 0;
        task[line_num].ticket = serv_p * 100;

        line_num += 1;

        /* Show error when exceed the maximum number of lines */
        if(line_num > MAX_PROC_NUM) {
            perror("Too many processes has been executed : You can only execute below 10 processes!");
            return;
        }
    }
    fclose(fp);
    proc_num = line_num;
}

/* sort Input */
void sortInput(Process *p){
    Process temp;
    for (int i = proc_num - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if(p[j].ariv_t > p[j+1].ariv_t){
                temp = p[j+1];
                p[j+1] = p[j];
                p[j] = temp;
            } else if(p[j].ariv_t == p[j+1].ariv_t && p[j].p_name > p[j+1].p_name) {
                temp = p[j+1];
                p[j+1] = p[j];
                p[j] = temp;
            }
        }
    }
}

void setTotalTime() {
    int sum = 0;
    for (int i = 0; i < proc_num; i++) {
        sum += task[i].serv_t;
    }
    total_time = sum;
}

/* Initialize array of Process structure and output */
void init () {

    parseInput();
    sortInput(task);
    setTotalTime();

    output = (char*)malloc(sizeof(char)*total_time);
}

void initReadyQueue(unsigned size){
	rq.rear = size-1;
	rq.front = size-1;
    rq.count = 0;
	rq.size = size;
	rq.array = (Process **)malloc(size * sizeof(Process *));
}

void enqueue(Process *item){
	rq.rear = (rq.rear + 1) % rq.size;
	if(rq.rear == rq.front){
		rq.rear--;
	}else{
		rq.array[rq.rear] = item;	
	}
    rq.count++;
}

Process *dequeue(){
	if(rq.front == rq.rear){
		return NULL;
	}
	rq.front = (rq.front + 1) % rq.size;
    rq.count--;
	return rq.array[rq.front];
}

Process *getFront() {
    int i = (rq.front + 1) % rq.size;
    return rq.array[i];
}

void printQueue() {
    printf("Queue : ");
    for (int i = 0; i < rq.size; i++)
    {
		int index = (rq.front + i) % rq.size;
        printf("%c ", rq.array[index]->p_name);
    }
}

int main() {
    init();
	initReadyQueue(10);
	enqueue(&task[0]);
    printf("%d ", rq.rear);
	enqueue(&task[1]);
    printf("%d ", rq.rear);
	enqueue(&task[2]);
    printf("%d ", rq.rear);
	enqueue(&task[3]);
    printf("%d ", rq.rear);

    for (int i = 1; i <= rq.count; i++)
    {
        int index = (rq.front + i) % rq.size;
        printf("%c ", rq.array[index]->p_name);
    }
    
}