#include <stdio.h>
#include <stdlib.h>

typedef struct{
  char * name;
  int age;
} person;

int main(){
  person * me = malloc(sizeof(person));
  me->name = "Keegan";
  me->age = 19;
  printf("%s's age is %d\n", me->name, me->age);
  free(me);
}
