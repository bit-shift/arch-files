// Header Comment
// Keegan Gyoery
// 2018

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int main(int argc, char *argv[]){
    int num;
    sscanf(argv[1],"%d", &num);
    char str[8];
    unsigned mask;
    int last3bits;
    int i = 6;
    while(i >= 0){
        mask = (1 << 3) - 1;
        last3bits = num & mask;
        str[i] = last3bits + '0';
        num = num >> 3;
        i--;
    }

    str[7] = '\0';
    printf("%s\n", str);
    

    return EXIT_SUCCESS;
}

