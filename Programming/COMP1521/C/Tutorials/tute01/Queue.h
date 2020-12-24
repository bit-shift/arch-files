#ifndef QUEUE_H
#define QUEUE_H

#define MAX_Q 6

typedef struct {
    int nitems;
    int head;
    int tail;
    int items[MAX_Q];
} Queue;

void initQueue(Queue *q);
void enterQueue(Queue *q, int n);
int leaveQueue(Queue *q);
int lengthQueue(Queue *q);
void showQueue(Queue q);

#endif
