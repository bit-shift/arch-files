#ifndef ALGORITHMS_H
#define ALGORITHMS_H

void printArray(int *array, int n, char *str);
void obliviousBubbleSort(int *array, int n);
void earlyExitBubbleSort(int *array, int n);
void selectionSort(int *array, int n);
void insertionSort(int *array, int n);
void quickSort(int *array, int lo, int hi);
int partition(int *array, int lo, int hi);
void mergeSort(int *array, int lo, int hi);
void merge(int *array, int lo, int mid, int hi);

#endif 
