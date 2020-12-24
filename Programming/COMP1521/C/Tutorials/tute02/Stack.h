#ifndef STACK_H
#define STACK_H
#define MAX_STACK 100

typedef char Item;

typedef struct _stack{
    int top;
    Item *items;
} Stack;

void initStack(Stack *s);
int pushStack(Stack *s, Item val);
Item popStack(Stack *s);
int isEmptyStack(Stack s);
void showStack(Stack s);

#endif
