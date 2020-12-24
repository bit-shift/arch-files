// Memory addresses of variables
// Keegan Gyoery z5197058
// 2018-02-27

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int num;
	printf("Type in a number: ");
	scanf("%d", &num);
	printf("The address is: %d\n", &num);
	printf("The address is: %#x\n", &num);
	
	return EXIT_SUCCESS;
}
