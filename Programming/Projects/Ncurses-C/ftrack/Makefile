# Makefile for Ftrack 
CC=gcc
CFLAGS=-Wall -Werror -g -std=gnu99 -lpthread
BINS=ftrack
OBJS=main.o menu.o

all : $(BINS)

ftrack: $(OBJS)
	$(CC) $(CFLAGS) -o ftrack $(OBJS)

main.o: main.c main.h
menu.o: menu.c menu.h

clean :
	rm -f $(BINS) $(OBJS) core
