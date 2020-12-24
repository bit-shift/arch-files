#ifndef TUTE_H
#define TUTE_H

typedef struct ListNode *Link;
 
typedef struct ListNode {
    int value;
    Link next;
} ListNode;
 
typedef Link List;
 
#define head(L)  (empty(L) ? -1 : (L)->value)
#define tail(L)  (empty(L) ? NULL : (L)->next)
#define empty(L) ((L) == NULL)
#define show(V) { printf("%d",(V)); }

int sorted(int *arr, int n);
int sumIterate(List l);
int sumRecursive(List l);
void drop(List l);
List copy(List l);

#endif
