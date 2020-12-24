// where_are_the_bits.c ... determine bit-field order
// COMP1521 Lab 03 Exercise
// Written by ...

#include <stdio.h>
#include <stdlib.h>

struct _bit_fields {
   unsigned int a : 4,
                b : 8,
                c : 20;
};

union bitfield {
    struct _bit_fields x;
    unsigned int i;
};

int main(void){

    union bitfield x;
    x.i = 8192 + 31;
    printf("%d\n", x.i);
    printf("%d\n", x.x.a);
    printf("%d\n", x.x.b);
    printf("%d\n", x.x.c);
    return 0;
}
