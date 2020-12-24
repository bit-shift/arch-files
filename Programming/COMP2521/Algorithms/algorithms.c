#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "algorithms.h"

static void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int *arr, int size, char* str) {
    if (arr == NULL) {
        fprintf(stderr, "Array provided points to NULL\n");
        exit(1);
    }
    printf("%s = [", str);
    for (int i = 0; i < size; i++) {
        // If we are printing the last element, don't print a trailing space
        if (i == size-1) printf("%d", arr[i]);
        else printf("%d, ", arr[i]);
    }
    printf("]\n");
}

void obliviousBubbleSort(int *array, int n) {
    for (int i = n-1; i >= 0; i--) {
        for (int j = 0; j < i ; j++) {
            if (array[j] > array[j+1]) {
                swap(&array[j], &array[j+1]);
            }
        }
    }
}

void earlyExitBubbleSort(int *array, int n) {
    int nswaps;
    do {
        nswaps = 0;
        for (int i = 0; i < n-1; i++) {
            if (array[i] > array[i+1]) {
                swap(&array[i], &array[i+1]);
                nswaps++;
            }
        }
    } while (nswaps > 0);
}

void selectionSort(int *array, int n) {
    int min, index;
    for (int i = 0; i < n-1; i++) {
        min = array[i];
        index = i;
        for (int j = i; j < n; j++) {
            if (array[j] < min) {
                min = array[j];
                index = j;
            }
        }
        swap(&array[i], &array[index]);
    }
}

void insertionSort(int *array, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (array[j] < array[j-1]) {
                swap(&array[j], &array[j-1]);
            }
            else break;
        }
    }
}

void quickSort(int *array, int lo, int hi) {
    int i;
    if (hi <= lo) return;
    i = partition(array, lo, hi);
    quickSort(array, lo, i-1);
    quickSort(array, i+1, hi);
}

int partition(int *array, int lo, int hi) {
    int pivot = array[hi];
    int i = lo-1;
    for (int j = lo; j < hi; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i+1], &array[hi]);
    return i+1;
}

void mergeSort(int *array, int lo, int hi) {
    if (lo < hi) {
        int mid = lo + (hi-lo)/2;
        mergeSort(array, lo, mid);
        mergeSort(array, mid+1, hi);
        merge(array, lo, mid, hi);
    }
}

void merge(int *array, int lo, int mid, int hi) {
    int i, j, k;
    int n1 = mid-lo+1;
    int n2 = hi-mid;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++) L[i] = array[lo+i];
    for (j = 0; j < n2; j++) R[j] = array[mid+1+j];

    i = 0;
    j = 0;
    k = lo;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) array[k++] = L[i++];
        else array[k++] = R[j++];
    }
    while (i < n1) array[k++] = L[i++];
    while (j < n2) array[k++] = R[j++];
}
