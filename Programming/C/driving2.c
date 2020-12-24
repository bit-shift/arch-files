// Can you drive?
// Keegan Gyoery z5197058
// 2018-02-27

#include <stdio.h>
#include <stdlib.h>

#define MIN_DRIVING_AGE 16
#define MAX_DRIVING_AGE 120

int main(int argc, char *argv[]){
	// Ask how old the user is
	printf("How old are you?\n");

	// Read in the users age
	int age;
	if(scanf("%d", &age) != 1){
		printf("Invalid input for age\n");
		return EXIT_FAILURE;
	}

	// Valid ages 0 or higher
	if(age < 0){
		printf("Invalid age\n");
		return EXIT_FAILURE;
	}

	// Invalid input ie not a number
	

	// Check if the user can drive if they are older than 16
	if(age < MIN_DRIVING_AGE){
	printf("You cannot drive!\n");
	}
	else if(age < MAX_DRIVING_AGE){
	printf("You can drive\n");
	}
	else{
	printf("You cannot drive!\n");
	}
	
	// Print the final message
	printf("Have a nice day!\n");

	return EXIT_SUCCESS;
}
