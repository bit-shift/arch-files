#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "BTree.h"

int isHeap(BTree t) {
    if (t == NULL) return 1;
    if (left(t) == NULL && right(t) == NULL) return 1;
    if (left(t) == NULL) return 0;

    if (right(t) == NULL && data(left(t)) < data(t)) return 1;

    if (data(left(t)) < data(t) && data(right(t)) < data(t)) {
        return isHeap(left(t)) && isHeap(right(t));
    }
    
    return 0;
}

int main(int argc, char *argv[]){


    return EXIT_SUCCESS;
}
