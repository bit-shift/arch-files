#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Heap.h"

struct HeapRep {
    int *items;
    int nitems;
    int nslots;
};

void showHeap(Heap h) {
    assert(h != NULL && h->items != NULL);
    int power = 1;
    for (int i = 1; i <= h->nitems; i++) { 
        if (i / pow(2, power) >= 1) {
            printf("\n");
            power++;
        }
        printf("%d ", h->items[i]);
    }
    printf("\n");
}

Heap newHeap(int N) {
    Heap new = malloc(sizeof(struct HeapRep));
    assert(new != NULL);
    new->items = malloc(sizeof(int)*(N+1));
    assert(new->items != NULL);
    for (int i = 0; i < N+1; i++) new->items[i] = -1;
    new->nitems = 0;
    new->nslots = N;
    return new;
}

int findHeap(Heap h, int i, int it) {
    assert(h != NULL && h->items != NULL);
    if (i > h->nitems) return 0;
    if (h->items[i] == it) return 1;
    else return findHeap(h, 2*i, it) || findHeap(h, 2*i+1, it);
}

void insertHeap(Heap h, int it) {
    assert(h != NULL && h->items != NULL);
    if (findHeap(h, 1, it)) return;
    h->nitems++;
    h->items[h->nitems] = it;
    fixUpHeap(h, h->nitems);
}

void fixUpHeap(Heap h, int i) {
    assert(h != NULL && h->items != NULL);
    assert(h->nitems < h->nslots);
    while (i > 1 && h->items[i/2] < h->items[i]) {
        int temp = h->items[i/2];
        h->items[i/2] = h->items[i];
        h->items[i] = temp;
        i = i/2;
    }
}

int deleteHeap(Heap h) {
    assert(h != NULL && h->items != NULL);
    int top = h->items[1];
    h->items[1] = h->items[h->nitems];
    h->items[h->nitems] = -1;
    h->nitems--;
    fixDownHeap(h, 1);
    return top;
}

void fixDownHeap(Heap h, int i) {
    assert(h != NULL && h->items != NULL);
    while (2*i <= h->nitems) {
        int j = 2*i;
        if (j < h->nitems && h->items[j] < h->items[j+1]) j++;
        if (h->items[i] >= h->items[j]) break;
        int temp = h->items[i];
        h->items[i] = h->items[j];
        h->items[j] = temp;
        i = j;
    }
}
