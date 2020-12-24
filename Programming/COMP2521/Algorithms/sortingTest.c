#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "algorithms.h"

int main(int argc, char *argv[]){
    int n, nvals, i = 0;
    printf("Please enter the size of the array: ");
    scanf("%d", &nvals);
    int vals[nvals];
    printf("Please enter the values in the array: ");
    while (scanf("%d", &n) == 1) {
        vals[i++] = n;
    }
    printArray(vals, nvals, "Unsorted");
    mergeSort(vals, 0, nvals-1);
    printArray(vals, nvals, "Sorted");

    return EXIT_SUCCESS;
}
