# COMP2521 Assignment 1 Makefile

CC=gcc
CFLAGS=-Wall -Werror -std=gnu99 -O -lm -g
BINS=textbuffer

all : $(BINS)

textbuffer : testTextbuffer.o textbuffer.o
	$(CC) -o textbuffer testTextbuffer.o textbuffer.o

textbuffer.o : textbuffer.c

testTextbuffer.o : testTextbuffer.c

clean :
	rm -f $(BINS) *.o core
