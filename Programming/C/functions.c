#include <stdio.h>
#include <stdbool.h>

int factorial(int number);
int multiply(int x, int y);

void addone(int *n){
  (*n)++;
}

int main() {
  int number = 4;
  int result = factorial(number);
  printf("%d\n", result);
  int n = 1;
  printf("Before: %d\n", n);
  addone(&n);
  printf("After: %d\n", n);

  printf("3 times 5 is: %d\n",multiply(1,5));
}

int factorial(int number){
  if(number == 0){
    return 1;
  }
  else {
    return number*factorial(number - 1);
  }
}

int multiply(int x, int y){
  if(x == 1){
    return y;
  }
  else if(x == 0){
    return 0;
  }
  else{
    return y + multiply(x-1,y);
  }
}
