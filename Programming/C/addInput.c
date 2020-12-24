#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	printf("Enter two numbers separated by a space\n");
	int num1, num2;
	scanf("%d %d", &num1, &num2);
	printf("The sum of the two numbers entered is: %d\n", num1+num2);
	
	return EXIT_SUCCESS;
}
