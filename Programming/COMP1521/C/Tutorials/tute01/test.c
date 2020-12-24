// Header Comment
// Keegan Gyoery
// 2018

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Queue.h"
#include "Queue.c"

int main(int argc, char *argv[]){
    Queue myq;
    initQueue(&myq);
    enterQueue(&myq, 3);
    enterQueue(&myq, 5);
    enterQueue(&myq, 9);
    enterQueue(&myq, 2);
    leaveQueue(&myq);
    showQueue(myq);

    return EXIT_SUCCESS;
}
