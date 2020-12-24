#include <stdio.h>
#include <stdbool.h>

int runner() {
  int count = 0;
  count++;
  return count;
}

int runner2() {
  static int count = 0;
  count++;
  return count;
}

int main(){
  printf("%d\n", runner());
  printf("%d\n", runner());
  printf("%d\n", runner2());
  printf("%d\n", runner2());
}
