CC=gcc
CFLAGS=-g -Wall --std=c99 -Iinclude
LIBS=-lm
TARGET= graph

OBJ_DIR = obj

DEPS = graph.h main.h
OBJS = graph.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)
