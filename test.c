#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int getrand(){
    srand((unsigned int)time(NULL));
    return rand() % 100;
}
int main() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 10; i++){
        printf("%d ", getrand());
    }
}