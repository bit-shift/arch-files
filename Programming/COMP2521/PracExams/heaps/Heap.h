#ifndef HEAP_H
#define HEAP_H

typedef struct HeapRep *Heap;

Heap newHeap(int N);
void insertHeap(Heap h, int it);
void fixUpHeap(Heap h, int i);
int findHeap(Heap h, int i, int it);
int deleteHeap(Heap h);
void fixDownHeap(Heap h, int i);
void showHeap(Heap h);

#endif
