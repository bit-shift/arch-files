#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>
#include "servcli.h"

void *server(void *varg)
{
	struct sockaddr_in my_addr, client_addr;
	socklen_t clen = sizeof(client_addr);
	int recvlen;			/* # bytes received */
	int server_fd;				/* our socket */
	char buff[BUFLEN];	/* receive buffer */
	char buf[BUFLEN];

	/* create a UDP socket */

	if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		fprintf(stderr, "Socket creation failed in UDP Server.\n");
		exit(EXIT_FAILURE);
	}

	/* bind the socket to any valid IP address and a specific port */

	memset((char *)&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons(S_PORT);

	if (bind(server_fd, (struct sockaddr *) &my_addr, sizeof(my_addr)) == -1) {
		fprintf(stderr, "Bind to socket failed in UDP Server.\n");
		exit(EXIT_FAILURE);
	}

	FILE *fileptr, *logptr;
	int header = 20;
	int ack = 0, sequ;
	char seq[header];

	fileptr = fopen("./received.pdf", "wb");
	logptr = fopen("./receiver_log.txt", "w");

	/* now loop, receiving data and printing what we received */
	for (;;) {
		recvlen = recvfrom(server_fd, buf, BUFLEN, 0, (struct sockaddr *)&client_addr, &clen);
		if (recvlen >= 0) {
			for (int i = 0; i < header; i++) seq[i] = buf[i];
			sequ = strtol(seq, NULL, 10);
			ack = sequ + recvlen - header;
			fprintf(logptr, "rcv\t\t%ld\t\t%d\t\t%d\t\t0\n", time(NULL), sequ, recvlen-header);
			fwrite(buf+header, recvlen-header, 1, fileptr);
		}

		sprintf(buff, "%d", ack);

		if (sendto(server_fd, buff, strlen(buff), 0, (struct sockaddr *) &client_addr, clen) == -1) {
			fprintf(stderr, "Send failed in UDP Server.\n");
		}
		
		fprintf(logptr, "snd\t\t%ld\t\t0\t\t0\t\t%d\n", time(NULL), ack);
		if (seq[15] == '1') {
			fclose(fileptr);
			fclose(logptr);
		}
	}
	/* never exits */
	return NULL;
}

int main(int argc, char **argv) {
	int s;
	pthread_t pserver;
	s = pthread_create(&pserver, NULL, server, NULL);
	pthread_join(pserver, NULL);

	return 0;
}
