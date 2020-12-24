#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Heap.h"

#define HEAP_MAX 1000

int main(int argc, char *argv[]){
    int n;
    Heap test = newHeap(HEAP_MAX);
    while (scanf("%d", &n) == 1) {
        insertHeap(test, n);
    }
    showHeap(test);
    insertHeap(test, 10);
    printf("------------------------\n");
    showHeap(test);
    int ret = deleteHeap(test);
    printf("------------------------\n");
    showHeap(test);


    return EXIT_SUCCESS;
}
