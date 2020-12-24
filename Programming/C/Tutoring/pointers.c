#include <stdlib.h>
#include <stdio.h>

int main (int argc, char* argv[]) {
	int num = 10;

	printf("\n");
	printf("Value stored in num is %d\n", num);
	printf("Address of num is %p\n", &num);
	printf("\n");

	int *pointer = &num;

	printf("\n");
	printf("Value stored in pointer is %p\n", pointer);
	printf("Value stored in the address that pointer points to is %d\n", *pointer);
	printf("\n");

	*pointer = 20;

	printf("\n");
	printf("Value stored in num is now %d\n", num);
	printf("Address of num is still %p\n", &num);
	printf("\n");

	int num2 = 30;
	pointer = &num2;

	printf("\n");
	printf("Value of pointer is now %p\n", pointer);
	printf("Value stored in the address that pointer points to is now %d\n", *pointer);
	printf("\n");
}
