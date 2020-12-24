#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "tute.h"

int sorted(int *array, int n) {
    for (int i = 0; i < n-1; i++) {
        if (array[i] > array[i+1]) return 0;
    }
    return 1;
}

int sumIterate(List l) {
    assert(l != NULL);
    Link curr = l;
    int sum = 0;
    while (curr != NULL) {
        sum += curr->value;
        curr = curr->next;
    }
    return sum;
}

int sumRecursive(List l) {
    if (l == NULL) return 0;
    else return l->value + sumRecursive(l->next);
}

void drop(List l) {
    if (l == NULL) return;
    else {
        Link hold = l->next;
        free(l);
        return drop(hold);
    }
}

static Link newNode(int value) {
    Link new = malloc(sizeof(struct ListNode));
    new->value = value;
    return new;
}

List copy(List l) {
    if (l == NULL) return NULL;
    else {
        Link insert = newNode(l->value);
        return insert->next = copy(l->next);
    }
}
