// Add two numbers together and print out the result
// Keegan Gyoery z5197058
// 2018-02-27

#include <stdio.h>
#include <stdlib.h>

int addNumbers (int num1, int num2);

int main(int argc, char *argv[]){
	int num1 = 2;
	int num2 = 3;

	int sum = addNumbers(num1, num2);
	printf("The sum of %d and %d is %d\n", num1, num2, sum);

	return EXIT_SUCCESS;
}

int addNumbers (int num1, int num2){
	int sum = num1 + num2;
	return sum;
}

