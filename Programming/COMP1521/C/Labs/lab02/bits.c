// Keegan Gyoery z5197058
// COMP1521 18s1 Week 02 Lab (warm-up)

#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	// Code to generate and display the largest "int" value

	int x = INT_MAX;
	printf("int %d, %x\n", x, x);

	// Code to generate and display the largest "unsigned int" value

    unsigned int y = UINT_MAX;
    printf("unsigned int %u, %x\n", y, y);

	// Code to generate and display the largest "long int" value

	long int xx = LONG_MAX;
	printf("long int %ld, %lx\n", xx, xx);

	// Code to generate and display the largest "unsigned long int" value

	unsigned long int xy = ULONG_MAX;
	printf("unsigned long int %lu, %lx\n", xy, xy);

	// Code to generate and display the largest "long long int" value

	long long int xxx = LLONG_MAX;
	printf("long long int %lld, %llx\n", xxx, xxx);

	// Code to generate and display the largest "unsigned long long int" value

	unsigned long long int xxy = ULLONG_MAX;
	printf("unsigned long long int %llu, %llx\n", xxy, xxy);

	return 0;
}

