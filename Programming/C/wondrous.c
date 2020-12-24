// Some beautiful numbers!
// Keegan Gyoery z5197058 
// 2018

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

static int steps = 0;

int wondrous(int number);

int main(int argc, char *argv[]){
    int number;
    printf("Please enter your favourite number: ");
    scanf("%d", &number);

    number = wondrous(number);
    
    return EXIT_SUCCESS;
}

int wondrous(int number){
    if(number == 1){
        printf("Steps: %d\n", steps);
        return number;
    }
    else{
        if(number % 2 == 0){
             number = number/2;
        }
        else{
            number = 3*number + 1;
        }
        printf("%d\n", number);
        steps++;
        return wondrous(number);
    }
}
