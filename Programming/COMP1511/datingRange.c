// Header Comment
// Keegan Gyoery
// 2018

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int main(int argc, char *argv[]){
    int age;
    printf("Please enter your age: ");
    scanf("%d", &age);
    int upperAge, lowerAge;
    if(age % 2 == 0){
        lowerAge = age/2 + 7;
    }
    else{
        lowerAge = age/2 + 8;
    }
    upperAge = age + 2*(age-lowerAge);
    if(lowerAge > age){
        printf("You are too young to be dating!\n");
    }
    else if(lowerAge == age){
        printf("You can date someone who is %d\n", age);
    }
    else{
        printf("You can date someone between %d and %d\n", lowerAge, upperAge);
    }

    return EXIT_SUCCESS;
}
