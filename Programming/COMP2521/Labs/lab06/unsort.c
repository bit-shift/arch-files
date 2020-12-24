// unsort.c ... make a sequence of numbers not sorted
// Usage: unsort [FileName]
// If no file name supplied, unsorts stdin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define MAX_RANDOM 1000000
#define swap(A,B) {int t; t = A; A = B; B = t;}

int main (int argc, char *argv[])
{
    FILE *in;

    if (argc == 1) 
      in = stdin;
    else {
      if ((in = fopen(argv[1],"r")) == NULL) {
         fprintf(stderr, "Can't open file '%s'\n",argv[1]);
         exit(1);
      }
    }
    int val;
    int count = 0;
    int *arr = malloc(MAX_RANDOM*sizeof(int));
    while (fscanf(in, "%d", &val) != EOF) {
        arr[count++] = val;
    }
    srand(time(NULL));
    for (int i = count-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(arr[j], arr[i]);
    }
    for (int k = 0; k < count; k++) {
        printf("%d\n", arr[k]);
    }

   return 0;
}      
