#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "textbuffer.h"

TBStack *initTBStack() {
    TBStackP new = malloc(sizeof(struct TBStack));
    assert(new != NULL);
    new->nTBs = 0;
    new->top = new->bottom = NULL;
    return new;
}

void pushTBStack(TBStackP tbstack, TBNodeP tbnode) {
    assert(tbstack != NULL && tbnode != NULL);
    if (tbstack->nTBs == 0) {
        tbstack->bottom = tbnode;
    }
    else {
        tbstack->top->prev = tbnode;
        tbnode->next = tbstack->top;
    }
    tbstack->top = tbnode;
    tbstack->nTBs++;
    if (tbstack->nTBs > 10) {
        trimTBStack(tbstack);
    }
}

TB popTBStack(TBStackP tbstack) {
    assert(tbstack != NULL);
    TB ret = NULL;
    if (tbstack->nTBs != 0) {
        ret = tbstack->top->state;
        tbstack->top = tbstack->top->next;
        tbstack->nTBs--;
    }
    return ret;
}

void trimTBStack(TBStackP tbstack) {
    assert(tbstack != NULL);
    TBNodeP hold = tbstack->bottom;
    tbstack->bottom = tbstack->bottom->prev;
    tbstack->bottom->next = NULL;
    releaseTB(hold->state);
    free(hold);
    tbstack->nTBs--;
}
