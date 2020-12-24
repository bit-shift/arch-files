CC=gcc
CFLAGS = --std=gnu99 -g -lpthread -lrt

all: udp-send udp-recv

udp-send: udp-send.o 
	$(CC) $(CFLAGS) -o udp-send udp-send.o $(LIBS)

udp-recv: udp-recv.o 
	$(CC) $(CFLAGS) -o udp-recv udp-recv.o $(LIBS)

udp-send.o: udp-send.c servcli.h

udp-recv.o: udp-recv.c servcli.h

clean:
	rm -f udp-send udp-recv udp-send.o udp-recv.o 
