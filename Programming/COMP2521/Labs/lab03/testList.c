// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

int main(int argc, char *argv[])
{
	DLList myList;
	myList = getDLList(stdin);
    printf("-------------------------------\n");
    printf("01-Reading from stdin\n");
    printf("-------------------------------\n");
    statusDLList(myList);
    printf("-------------------------------\n");
	putDLList(stdout,myList);
	assert(validDLList(myList));
    printf("-------------------------------\n");

    FILE *fp;
    fp = fopen("test1","r");
    DLList myList1;
    myList1 = getDLList(fp);

    printf("MANY LINE LIST TESTING\n");

    printf("-------------------------------\n");
    printf("02-Add before, middle\n");
    printf("-------------------------------\n");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    printf("-------------------------------\n");
    printf("move 1 line down\n");
    printf("-------------------------------\n");
    DLListMoveTo(myList1, 2);
    statusDLList(myList1);
    printf("-------------------------------\n");
    printf("insert yeehaw\n");
    printf("-------------------------------\n");
    DLListBefore(myList1, "yeehaw");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    assert(validDLList(myList1));
    printf("-------------------------------\n");

    printf("-------------------------------\n");
    printf("03-Add before, first\n");
    printf("-------------------------------\n");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    printf("-------------------------------\n");
    printf("move to first\n");
    printf("-------------------------------\n");
    DLListMoveTo(myList1, 1);
    statusDLList(myList1);
    printf("-------------------------------\n");
    printf("insert im the first line\n");
    printf("-------------------------------\n");
    DLListBefore(myList1, "im the first line");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    assert(validDLList(myList1));
    printf("-------------------------------\n");

    printf("-------------------------------\n");
    printf("04-Add before, last\n");
    printf("-------------------------------\n");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    printf("-------------------------------\n");
    printf("move to last\n");
    printf("-------------------------------\n");
    DLListMoveTo(myList1, 10);
    statusDLList(myList1);
    printf("-------------------------------\n");
    printf("insert im the second last line\n");
    printf("-------------------------------\n");
    DLListBefore(myList1, "im the second last line");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    assert(validDLList(myList1));
    printf("-------------------------------\n");

    printf("-------------------------------\n");
    printf("05-Add after, middle\n");
    printf("-------------------------------\n");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    printf("-------------------------------\n");
    printf("move to middle\n");
    printf("-------------------------------\n");
    DLListMoveTo(myList1, 4);
    statusDLList(myList1);
    printf("-------------------------------\n");
    printf("insert yeehaw2\n");
    printf("-------------------------------\n");
    DLListAfter(myList1, "yeehaw2");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    assert(validDLList(myList1));
    printf("-------------------------------\n");

    printf("-------------------------------\n");
    printf("06-Add after, first\n");
    printf("-------------------------------\n");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    printf("-------------------------------\n");
    printf("move to first\n");
    printf("-------------------------------\n");
    DLListMoveTo(myList1, 1);
    statusDLList(myList1);
    printf("-------------------------------\n");
    printf("insert im the second line\n");
    printf("-------------------------------\n");
    DLListAfter(myList1, "im the second line");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    assert(validDLList(myList1));
    printf("-------------------------------\n");

    printf("-------------------------------\n");
    printf("07-Add after, last\n");
    printf("-------------------------------\n");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    printf("-------------------------------\n");
    printf("move to last\n");
    printf("-------------------------------\n");
    DLListMoveTo(myList1, 15);
    statusDLList(myList1);
    printf("-------------------------------\n");
    printf("insert im the last line\n");
    printf("-------------------------------\n");
    DLListAfter(myList1, "im the last line");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    assert(validDLList(myList1));
    printf("-------------------------------\n");

    printf("-------------------------------\n");
    printf("08-Delete current, middle\n");
    printf("-------------------------------\n");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    printf("-------------------------------\n");
    printf("move to middle\n");
    printf("-------------------------------\n");
    DLListMoveTo(myList1, 6);
    statusDLList(myList1);
    printf("-------------------------------\n");
    printf("delete yeehaw2\n");
    printf("-------------------------------\n");
    DLListDelete(myList1);
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    assert(validDLList(myList1));
    printf("-------------------------------\n");

    printf("-------------------------------\n");
    printf("09-Delete current, first\n");
    printf("-------------------------------\n");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    printf("-------------------------------\n");
    printf("move to first\n");
    printf("-------------------------------\n");
    DLListMoveTo(myList1, 1);
    statusDLList(myList1);
    printf("-------------------------------\n");
    printf("delete im the first line\n");
    printf("-------------------------------\n");
    DLListDelete(myList1);
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    assert(validDLList(myList1));
    printf("-------------------------------\n");

    printf("-------------------------------\n");
    printf("10-Delete current, last\n");
    printf("-------------------------------\n");
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    printf("-------------------------------\n");
    printf("move to last\n");
    printf("-------------------------------\n");
    DLListMoveTo(myList1, 20);
    statusDLList(myList1);
    printf("-------------------------------\n");
    printf("delete im the last line\n");
    printf("-------------------------------\n");
    DLListDelete(myList1);
    statusDLList(myList1);
    printf("-------------------------------\n");
    putDLList(stdout, myList1);
    assert(validDLList(myList1));
    printf("-------------------------------\n");

    FILE *fp2;
    fp2 = fopen("test3","r");
    DLList myList3;
    myList3 = getDLList(fp2);

    printf("EMPTY LIST TESTING\n");

    printf("-------------------------------\n");
    printf("11-Delete current, empty\n");
    printf("-------------------------------\n");
    statusDLList(myList3);
    printf("-------------------------------\n");
    putDLList(stdout, myList3);
    printf("-------------------------------\n");
    printf("delete\n");
    printf("-------------------------------\n");
    DLListDelete(myList3);
    statusDLList(myList3);
    printf("-------------------------------\n");
    putDLList(stdout, myList3);
    assert(validDLList(myList3));
    printf("-------------------------------\n");

    printf("-------------------------------\n");
    printf("12-Add before, empty\n");
    printf("-------------------------------\n");
    statusDLList(myList3);
    printf("-------------------------------\n");
    putDLList(stdout, myList3);
    printf("-------------------------------\n");
    printf("add first line (before)\n");
    printf("-------------------------------\n");
    DLListBefore(myList3, "first line (before)");
    statusDLList(myList3);
    printf("-------------------------------\n");
    putDLList(stdout, myList3);
    assert(validDLList(myList3));
    printf("-------------------------------\n");

    printf("ONE LINE TESTING\n");

    printf("-------------------------------\n");
    printf("13-Delete current, one\n");
    printf("-------------------------------\n");
    statusDLList(myList3);
    printf("-------------------------------\n");
    putDLList(stdout, myList3);
    printf("-------------------------------\n");
    printf("delete first line\n");
    printf("-------------------------------\n");
    DLListDelete(myList3);
    statusDLList(myList3);
    printf("-------------------------------\n");
    putDLList(stdout, myList3);
    assert(validDLList(myList3));
    printf("-------------------------------\n");

    printf("EMPTY LIST TESTING\n");

    printf("-------------------------------\n");
    printf("14-Add after, empty\n");
    printf("-------------------------------\n");
    statusDLList(myList3);
    printf("-------------------------------\n");
    putDLList(stdout, myList3);
    printf("-------------------------------\n");
    printf("add first line (after)\n");
    printf("-------------------------------\n");
    DLListAfter(myList3, "first line (after)");
    statusDLList(myList3);
    printf("-------------------------------\n");
    putDLList(stdout, myList3);
    assert(validDLList(myList3));
    printf("-------------------------------\n");

	return 0;
}
