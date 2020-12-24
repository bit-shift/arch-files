// Complex Numbers
// Keegan Gyoery z5197058
// 2018-02-27

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

typedef struct _complex {
	double re;
	double im;
} complex;

void complexPrint(complex z);
complex complexAdd(complex z, complex w);
complex complexSub(complex z, complex w);
int complexCompare(complex z, complex w);

int main(int argc, char *argv[]){
	complex z = {
		.re = 5,
		.im = 7
	};
	
	complex w = {
		.re = 17,
		.im = 8
	};
	
	complex sum = complexAdd(z,w);
	complex minus = complexSub(z,w);
	
	complexPrint(z);
	complexPrint(w);
	complexPrint(sum);
	complexPrint(minus);
	
	return EXIT_SUCCESS;
}

complex complexAdd(complex z, complex w){
	complex holder;
	holder.re = z.re + w.re;
	holder.im = z.im + w.im;
	return holder;
}

complex complexSub(complex z, complex w){
	complex holder = {
		.re = z.re - w.re,
		.im = z.im - w.im
	};
	return holder;
}

int complexCompare(complex z, complex w){
	return (z.re == w.re) && (z.im == w.im);
}

void complexPrint(complex z){
	printf("%lf + %lfi\n", z.re, z.im);
}
