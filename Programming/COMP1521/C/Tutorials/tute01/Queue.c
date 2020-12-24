// Header Comment
// Keegan Gyoery
// 2018

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Queue.h"

void initQueue(Queue *q){
    q->nitems = 0;
    q->head = 0;
    q->tail = 0;
    for(int i = 0; i < MAX_Q; i++){
        q->items[i] = 0;
    }
}

void enterQueue(Queue *q, int n){
    q->items[q->tail] = n;
    q->tail += 1;
}

int leaveQueue(Queue *q){
    int ret = q->items[q->head];
    for(int i = 0; i < MAX_Q - 1; i++){
        q->items[i] = q->items[i+1];
    }
    q->tail -= 1;
    return ret;
}

int lengthQueue(Queue *q){
    if(q->items[q->head] == 0){
        return q->head;
    }
    else {
        return q->tail + 1;
    }
}

void showQueue(Queue q){
    for(int i = 0; i < q.tail; i++){
        printf("%d ", q.items[i]);
    }
}
