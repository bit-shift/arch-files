// While loop fun
// Keegan Gyoery z5197058
// 2018-02-27

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int l;
	printf("Enter a number please: ");
	scanf("%d", &l);
	int i = 0;
	while(i < l){
		printf("%d\n", i);
		i++;
	}

	return EXIT_SUCCESS;
}
