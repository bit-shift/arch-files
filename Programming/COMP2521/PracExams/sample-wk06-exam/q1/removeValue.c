// removeValue.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "removeValue" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/



/*void removeValue(DLList L, int value) {
    assert(L != NULL);
    if (L->first == NULL) {
        return;
    }
	if (L->nitems == 1) {
		if (L->first->value == value) {
			free(L->first);
			L->curr = L->first = L->last = NULL;
			L->nitems--;
		}
		return;
	}
    L->curr = L->first->next;
	while (L->curr->next != NULL) {
		if (L->curr->value == value) {
			DLListNode *hold = L->curr;
			L->curr->prev->next = L->curr->next;
			L->curr->next->prev = L->curr->prev;
			L->curr = hold->prev;
			free(hold);
			L->nitems--;
		}
		L->curr = L->curr->next;
	}
	if (L->first->value == value) {
		DLListNode *hold = L->first;
		L->first = L->first->next;
		L->first->prev = NULL;
		free(hold);
		L->nitems--;
	}
	if (L->last->value == value) {
		if (L->nitems > 1) {
			DLListNode *hold = L->last;
			L->last = L->last->prev;
			L->last->next = NULL;
			free(hold);
			L->nitems--;
		}
		else {
			free(L->last);
			L->curr = L->first = L->last = NULL;
			L->nitems --;
		}
	}
	L->curr = L->first;
	return;
}*/

void removeValue(DLList L, int value) {
	assert(L != NULL);
	DLListNodeP iterator = L->first;
	DLListNodeP hold;
	while (iterator != NULL) {
		if (iterator->value == value) {
			if (iterator->prev == NULL && iterator->next == NULL) {
				L->first = L->last = NULL;
			}
			else if (iterator->prev == NULL) {
				iterator->next->prev = NULL;
				L->first = iterator->next;
			}
			else if (iterator->next == NULL) {
				iterator->prev->next = NULL;
				L->last = iterator->prev;
			}
			else {
				iterator->prev->next = iterator->next;
				iterator->next->prev = iterator->prev;
			}
			L->nitems--;
			hold = iterator;
			iterator = iterator->next;
			free(hold);
		} 
		else {
			iterator = iterator->next;
		}
	}
	L->curr = L->first;	
	return;
}
