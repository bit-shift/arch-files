// Header Comment
// Keegan Gyoery
// 2018

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int fd = open("octal.c", O_RDONLY);
    if (fd < 0) {
       perror(NULL);
       exit(1);
    }



    return EXIT_SUCCESS;
}
