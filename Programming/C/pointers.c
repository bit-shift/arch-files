#include <stdio.h>

int main(){
  int a = 1;
  int * pointer_to_a = &a;

  a += 1;
  * pointer_to_a += 1;
  printf("Value of a is %d\n", a);
}
