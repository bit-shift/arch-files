CC=gcc
CFLAGS=-Wall -Werror -std=gnu99 -g
OBJS=sortingTest.o algorithms.o

all : sortingTest

sortingTest : $(OBJS)
	$(CC) $(CFLAGS) -o sortingTest $(OBJS)

sortingTest.o : sortingTest.c
algorithms.o : algorithms.c algorithms.h

clean :
	rm -f sortingTest $(OBJS)
