// Examine behaviour of strings and character arrays
// Keegan Gyoery z5197058
// 2018-02-27

#include <stdio.h>
#include <stdlib.h>

void showCharArray(char *array);

int main(int argc, char *argv[]){
	char str[7] = {'A','N','D','R','E','W','\0'};
	showCharArray(str);
	printf("\n");
	printf("%s\n", str);

	return EXIT_SUCCESS;
}

void showCharArray(char *array){
	int index = 0;
	while(array[index] != '\0'){
		putchar(array[index]);
		index++;
	}	
}
