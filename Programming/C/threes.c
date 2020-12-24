// 
// Keegan Gyoery z5197058
// 2018-02-27

#include <stdio.h>
#include <stdlib.h>

int removeThrees(int num);

int main(int argc, char *argv[]){
	int input;
	printf("Please enter a number: ");
	scanf("%d", &input);
	input = removeThrees(input);
	printf("Number is %d\n", input);
}

int removeThrees(int num){
	if(num % 3 == 0){
		num = -1;	
	}
	
	return num;
}
