/*
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "Url.h"
#include "permute.h"
#include "scaledFootrule.h"

Function to swap values at two pointers
void swap(int *x, int *y) 
{ 
    char temp; 
    temp = *x; 
    *x = *y; 
    *y = temp; 
} 
  
Function to print permutations of string 
   This function takes three parameters: 
   1. String 
   2. Starting index of the string 
   3. Ending index of the string.
void permute(int *a, int l, int r, UrlList unionRanking, UrlList *lists, int argc, double *minWCP, int *gloperm) 
{ 
   int i; 
   if (l == r) {
        computeTotalWCP(unionRanking, lists, argc, a, r+1, minWCP, gloperm);
   }
   else
   { 
       for (i = l; i <= r; i++) 
       { 
          swap((a+l), (a+i)); 
          permute(a, l+1, r, unionRanking, lists, argc, minWCP, gloperm); 
          swap((a+l), (a+i)); //backtrack 
       } 
   } 
} 

int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) result *= i;
    return result;
}
*/
