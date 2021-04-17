#include <stdio.h>
#define PROC_NUM 3
#define COMMON 300

typedef struct{
    char proc_id;
    int tickets;
    int stride;
    int pass_val;
}Process;

void initProcess(Process *p) {
    p[0].proc_id = 'A';
    p[0].tickets = 1;
    p[0].pass_val = 0;

    p[1].proc_id = 'B';
    p[1].tickets = 3;
    p[1].pass_val = 0;

    p[2].proc_id = 'C';
    p[2].tickets = 5;
    p[2].pass_val = 0;
}

void setStride(Process *p){
    for (int i = 0; i < PROC_NUM; i++) {
        p[i].stride = COMMON / p[i].tickets;
    }
}

void stride_sch(Process *p) {
    for(int i = 0; i < 10; i++) {
        int min_idx = 0;
        int min_pass = 1000; //가장 작은 pass val 을 구하기위한 임의의 숫자

        /* 가장 작은 pass val을 가진 process의 index 구하기*/
        for (int i = 0; i < PROC_NUM; i++)
        {
            if(p[i].pass_val < min_pass) {
                min_pass = p[i].pass_val;
                min_idx = i;
            }
        }
        for (int i = 0; i < PROC_NUM; i++)
        {
            printf("%3d ",p[i].pass_val);
        }

        p[min_idx].pass_val += p[min_idx].stride;
        printf("%c \n", p[min_idx].proc_id);
    }
}

int main(){
    Process p[PROC_NUM];

    initProcess(p);
    setStride(p);
    stride_sch(p);
}