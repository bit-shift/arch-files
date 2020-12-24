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

int main(int argc, char *argv[]){
    complex z = {0,0};
    printf("z is at %p\n", &z);
    printf("size of(complex) = %zu\n", sizeof(complex));
    printf("size of(z) = %zu\n", sizeof(z));

    complex *cc = calloc(1, sizeof(complex));
    assert(cc != NULL);
    printf("cc is at %p\n", cc);
    free(cc);
    return EXIT_SUCCESS;
}
