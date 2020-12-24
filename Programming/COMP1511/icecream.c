// Header Comment
// Keegan Gyoery
// 2018

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define MAX_MONEY 10

int main(int argc, char *argv[]){
    double scoops, costPerScoop;
    printf("How many scoops? ");
    scanf("%lf", &scoops);
    printf("How many dollars does each scoop cost? ");
    scanf("%lf", &costPerScoop);
    double costTotal = scoops * costPerScoop;
    
    if(costTotal > MAX_MONEY){
        printf("Oh no, you dont have enough money!\n");
    }
    else{
        printf("You have enough money!\n");
    }

    return EXIT_SUCCESS;
}
