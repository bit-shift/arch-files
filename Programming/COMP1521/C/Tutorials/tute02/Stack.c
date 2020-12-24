// Header Comment
// Keegan Gyoery
// 2018

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Stack.h"

void initStack(Stack *s){
    s->items = malloc(MAX_STACK * sizeof(Item));
    assert(s->items != NULL);
    s->top = -1;
}

int pushStack(Stack *s, Item val){
    s->top++;
    if(s->top >= MAX_STACK){
        return 0;
    }
    else{
        s->items[s->top] = val;
        return 1;
    }
}

Item popStack(Stack *s){
    if(s->top <= -1){
        return '#';
    }
    else{
        Item ret = s->items[s->top];
        s->top--;
        return ret;
    }
}

int isEmptyStack(Stack s){
    if(s.top <= -1){
        return 1;
    }
    else{
        return 0;
    }
}

void showStack(Stack s){
    for(int i = 0; i <= s.top; i++){
        printf("%c ", s.items[i]);
    }
    printf("\n");
}
