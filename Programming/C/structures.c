#include <stdio.h>

struct point{
  int x;
  int y;
};

typedef struct{
  char * name;
  int age;
} person;

int main(){
  struct point p;
  p.x = 5;
  p.y = 10;

  person k;
  k.name = "Keegan";
  k.age = 19;

  printf("%s's age is %d\n", k.name, k.age);

}
