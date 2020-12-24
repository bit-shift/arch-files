#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "queue.h"
#include "textbuffer.h"

TBQueue *initTBQueue() {
    TBQueueP new = malloc(sizeof(struct TBQueue));
    assert(new != NULL);
    new->nitems = 0;
    new->head = new->tail = NULL;
    return new;
}

void enterTBQueue(TBQueueP tbqueue, QueueNode *queuenode) {
    assert(tbqueue != NULL && queuenode != NULL);
    if (tbqueue->nitems == 0) {
        tbqueue->head = queuenode;
    }
    else {
        tbqueue->tail->next = queuenode;
        queuenode->prev = tbqueue->tail;
    }
    tbqueue->tail = queuenode;
}

QueueNode *leaveTBQueue(TBQueueP tbqueue) {
    assert(tbqueue != NULL);
    QueueNode *ret = NULL;
    if (tbqueue->nitems != 0) {
        ret = tbqueue->head;
        tbqueue->head = tbqueue->head->next;
        tbqueue->nitems--;
    }
    return ret;
}
