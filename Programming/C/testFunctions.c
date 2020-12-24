// Playing with Functions
// Keegan Gyoery z5197058
// 2018-02-27

#include <stdio.h>
#include <stdlib.h>

int doubled (int n);

int main(int argc, char *argv[]){
	int num = 24;
	printf("%d doubled is %d\n", num, doubled(num));

	return EXIT_SUCCESS;
}

int doubled(int n){
	return n*2;
}
