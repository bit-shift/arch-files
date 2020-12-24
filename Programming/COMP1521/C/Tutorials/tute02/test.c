// Header Comment
// Keegan Gyoery
// 2018

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Stack.h"
#include "Stack.c"

void fatal(char *msg);

int main(int argc, char *argv[]){
    Stack s;
    initStack(&s);
    char ch;

    while((ch = getchar()) != EOF){
        if(ch == '(' || ch == '[' || ch == '{'){
            if(!pushStack(&s, ch)){
                fatal("Too much nesting");
            }
            showStack(s);
        }
        else if(ch == ')'){
            if(popStack(&s) != '('){
                fatal("Mismatch of (..)");
            }
            showStack(s);
        }
        else if(ch == ']'){
            if(popStack(&s) != '['){
                fatal("Mismatch of [..]");
            }
            showStack(s);
        }
        else if(ch == '}'){
            if(popStack(&s) != '{'){
                fatal("Mismatch of {..}");
            }
            showStack(s);
        }
    }
    if(!isEmptyStack(s)){
        fatal("Insufficient closing brackets");
    }
    printf("Matched\n");
    return EXIT_SUCCESS;
}

void fatal(char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(1);
}
