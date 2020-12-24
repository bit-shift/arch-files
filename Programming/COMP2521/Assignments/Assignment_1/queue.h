#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode {
    char *string;
    struct QueueNode *next;
    struct QueueNode *prev;
} QueueNode;

typedef struct TBQueue {
    int nitems;
    QueueNode *head;
    QueueNode *tail;
} TBQueue;

typedef QueueNode *QueueNodeP;

typedef TBQueue *TBQueueP;

TBQueue *initTBQueue();

void enterTBQueue(TBQueueP tbqueue, QueueNode *queuenode);

QueueNode *leaveTBQueue(TBQueueP tbqueue);

#endif
