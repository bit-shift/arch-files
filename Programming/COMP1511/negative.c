// Header Comment
// Keegan Gyoery
// 2018

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int main(int argc, char *argv[]){
    int n;
    printf("Please enter a number: ");
    scanf("%d", &n);
    if(n < 0){
        printf("Don't be so negative!\n");
    }
    else if(n > 0){
        printf("Keep being positive!\n");
    }
    else{
        printf("No comment\n");
    }

    return EXIT_SUCCESS;
}
