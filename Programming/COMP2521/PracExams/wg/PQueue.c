#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "PQueue.h"

struct PQueueNode {
    Item vertex;
    Item weight;
    PNode next;
};

struct PQueueRep {
    PNode head, tail;
    int nitems;
};

static PNode newPNode(Item vertex, Item weight) {
    PNode new = malloc(sizeof(struct PQueueNode));
    assert(new != NULL);
    new->vertex = vertex;
    new->weight = weight;
    return new;
}

PQueue newPQueue() {
    PQueue new = malloc(sizeof(struct PQueueRep));
    assert(new != NULL);
    new->nitems = 0;
    new->head = new->tail = NULL;
    return new;
}

void dropPQueue(PQueue pq) {
    assert(pq != NULL);
    PNode curr = pq->head;
    PNode hold;
    while (curr != NULL) {
        hold = curr;
        curr = curr->next;
        free(hold);
    }
    free(pq);
}

void showPQueue(PQueue pq) {
    assert(pq != NULL);
    PNode curr = pq->head;
    while (curr != NULL) {
        if (curr == pq->tail) {
            printf("[(%d)––(%d)]\n", curr->vertex, curr->weight);
        }
        else {
            printf("[(%d)––(%d)] <- ", curr->vertex, curr->weight);
        }
        curr = curr->next;
    }
}

void PQueueJoin(PQueue pq, Item vertex, Item weight) {
    assert(pq != NULL && vertex > -1 && weight > 0);
    PNode insert = newPNode(vertex, weight);
    PNode curr = pq->head;
    PNode hold;
    if (curr == NULL) {
        pq->head = pq->tail = insert;
    }
    else if (curr->next == NULL) {
        curr->next = insert;
        curr->tail
    while (curr->next != NULL) {
        if (curr->next->weight > insert->weight) {
            hold = curr->next;
            curr->next = insert;
            insert->next = hold;




}
Item PQueueLeave(PQueue); // remove item from queue
int PQueueIsEmpty(PQueue); // check for no items
