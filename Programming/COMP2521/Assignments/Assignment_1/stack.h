#ifndef STACK_H
#define STACK_H
#include "textbuffer.h"

typedef struct TBNode {
    TB State;
    struct TBNode *next;
    struct TBNode *prev;
} TBNode;

typedef struct TBStack {
    int nTBs;
    TBNode *top;
    TBNode *bottom;
} TBStack;

typedef TBNode *TBNodeP;

typedef TBStack *TBStackP;

TBStack *initTBStack();

void pushTBStack(TBStackP tbstack, TBNodeP tbnode);

TB popTBStack(TBStackP tbstack);

void trimTBStack(TBStackP tbstack);

#endif
