// Header Comment
// Keegan Gyoery
// 2018

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

typedef struct _complex {
    double re, im;
} complex;

complex *readComplexNumbers(int n);

int main(int argc, char *argv[]){
    printf("How many complex numbers would you like: ");
    int n;
    scanf("%d", &n);

    complex *values = readComplexNumbers(n);
    printf("values[0] = %lf + %lfi\n", values[0].re, values[0].im);
    free(values);

    return EXIT_SUCCESS;
}

complex *readComplexNumbers(int n){
    complex *values = calloc(n, sizeof(complex));
    assert(values != NULL);

    int i = 0;
    while(i < n){
        printf("x = ");
        scanf("%lf", &(values[i].re));
        printf("y = ");
        scanf("%lf", &(values[i].im));
        i++;
    }
    return values;
}
