// Playing around with arrays
// Keegan Gyoery z5197058
// 2018-02-27

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 42

int main(int argc, char *argv[]){
	int array[ARRAY_SIZE] = {0};

	int i = 0;
	while(i < ARRAY_SIZE){
		array[i] = i;
		printf("%d\n", array[i]);
		i++;
	}
	
	return EXIT_SUCCESS;
}
