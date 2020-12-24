#include <stdio.h>

typedef struct{
  char * name;
  int age;
} person;

void addoneage(person * p){
  (*p).age++;
}

int main(){
  person k;
  k.name = "Keegan";
  k.age = 18;

  addoneage(&k);
  printf("%s's age is now %d\n", k.name, k.age);
}
