#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
	int num1 = 0;
	int num2 = 1390;
	int maxam = 1390;

	int num1f;
	int num2f;

	double price1 = 81.16;
	double price2 = 7.136;

	int total = 9920;
	double low = (total - (num1*price1 + num2*price2));
	double temp;


	for (int i = 0; i <= maxam; i++) {
		num1 = i;
		for (int j = 0; j <= maxam; j++) {
			num2 = j;
			temp = (total - (num1*price1 + num2*price2));
			if (temp >= 0 && temp < low) {
				low = temp;
				num1f = num1;
				num2f = num2;
			}
		}
	}

	printf("Number of stock 1 ($81.16) is %d\nNumber of stock 2 ($7.136) is %d\n", num1f, num2f);
	printf("$10,000 - $81.16*%d - $7.136*%d = $%.2f\n", num1f, num2f, low);

	return 0;
}

