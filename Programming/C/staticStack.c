// Header Comment
// Keegan Gyoery z5197058
// 2018-03-01

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE 100

typedef int Item;
typedef struct {
    int top;
    Item items[MAX_SIZE]; 
} Stack;

void initStack(Stack *s);
int pushStack(Stack *s, Item val);
Item popStack(Stack *s);
int isEmptyStack(Stack s);
void showStack(Stack s);

int main(int argc, char *argv[]){
    Stack myStack;
    int x;
    initStack(&myStack);

    while(scanf("%d", &x) == 1){
        if(!pushStack(&myStack, x)){
            break;
        }
        showStack(myStack);
    }

    while(!isEmptyStack(myStack)){
        printf("%d\n", popStack(&myStack));
    }

    return EXIT_SUCCESS;
}

void initStack(Stack *s){
    s->top = 0;
}

int pushStack(Stack *s, Item val){
    if(s->top == MAX_SIZE){
        return 0;
    }
    s->items[s->top] = val;
    s->top++;
    return 1;
}

Item popStack(Stack *s){
    if(s->top == 0){
        return -1;
    }
    s->top--;
    return s->items[s->top];
}

int isEmptyStack(Stack s){
    return (s.top == 0);
}

void showStack(Stack s){
    printf("Base ");
    for(int i = 0; i < s.top; i++){
        printf("%d ", s.items[i]);
    }
    printf("Top\n");
}
