#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>
#include "servcli.h"

void *client(void *varg)
{
	struct sockaddr_in my_addr, server_addr;
	socklen_t slen=sizeof(server_addr);
	int client_fd;
	int recvlen;		/* # bytes in acknowledgement message */
	char buf[BUFLEN];	/* message buffer */
	char *host = "127.0.0.1";	/* change this to use a different server */

	/* create a socket */

	if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		fprintf(stderr, "Socket creation failed in UDP Client.\n");
		exit(EXIT_FAILURE);
	}

	struct timeval response_timeout;
	response_timeout.tv_sec = 1;

	if ((setsockopt(client_fd, SOL_SOCKET, SO_RCVTIMEO, &response_timeout, sizeof(response_timeout))) == -1) {
		fprintf(stderr, "Setsockopt failed in UDP Client.\n");
		exit(EXIT_FAILURE);
	}

	/* bind it to all local addresses and pick any port number */

	memset((char *)&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons(20000);

	if (bind(client_fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1) {
		fprintf(stderr, "Bind to socket failed in UDP Client.\n");
		exit(EXIT_FAILURE);
	}       

	/* now define server_addr, the address to whom we want to send messages */
	/* For convenience, the host address is expressed as a numeric IP address */
	/* that we will convert to a binary format via inet_aton */

	memset((char *) &server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(S_PORT);

	if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
		fprintf(stderr, "IP Address conversion failed in UDP Client.\n");
		exit(EXIT_FAILURE);
	}

	FILE *fileptr, *logptr;
	char *buffer; 
	int MSS = 400;
	long filelen, size = MSS, header = 20;
	int sent, count = -1;
	int seq = 0;
	int ack;
	double drop_prob = 0.1;
	double drand;

	srand(time(NULL));

	char *filename = "./2012.pdf";
	logptr = fopen("./sender_log.txt", "w");

	fileptr = fopen(filename, "rb");
	fseek(fileptr, 0, SEEK_END);
	filelen = ftell(fileptr);
	rewind(fileptr);

	while (filelen > 0) {
		drand = (double) rand()/RAND_MAX;
		while (drand < drop_prob) {
			recvlen = recvfrom(client_fd, buf, BUFLEN, 0, (struct sockaddr *) &server_addr, &slen);
			count++;
			if (count == 0) fprintf(logptr, "drp\t\t%ld\t\t%d\t\t%ld\t\t0\n", time(NULL), seq, size);
			else fprintf(logptr, "rtx-drp\t\t%ld\t\t%d\t\t%ld\t\t0\n", time(NULL), seq, size);
			drand = (double) rand()/RAND_MAX;
		}

		if (filelen < MSS) size = filelen;
		else size = MSS;
		filelen -= size;

		buffer = malloc((size+header)*sizeof(char));
		fread(buffer+header, size, 1, fileptr); 
		sprintf(buffer, "%d", seq);
		if (filelen == 0) buffer[15] = '1';
		else buffer[15] = '0';

		sent = sendto(client_fd, buffer, size+header, 0, (struct sockaddr *) &server_addr, slen);
		if (sent == -1) {
			fprintf(stderr, "Send failed in UDP Client.\n");
		}

		
		if (count == -1) fprintf(logptr, "snd\t\t%ld\t\t%d\t\t%ld\t\t0\n", time(NULL), seq, size);
		else fprintf(logptr, "rtx\t\t%ld\t\t%d\t\t%ld\t\t0\n", time(NULL), seq, size);
		free(buffer);
		seq += size;

		recvlen = recvfrom(client_fd, buf, BUFLEN, 0, (struct sockaddr *) &server_addr, &slen);
		if (recvlen >= 0) {
			buf[recvlen] = '\0';
			ack = strtol(buf, NULL, 10);
			fprintf(logptr, "rcv\t\t%ld\t\t0\t\t0\t\t%d\n", time(NULL), seq);
		}
		count = -1;
	}
	fclose(logptr);
	fclose(fileptr);
	close(client_fd);
	return NULL;
}

int main(int argc, char **argv) {
	int c;
	pthread_t pclient;
	c = pthread_create(&pclient, NULL, client , NULL);
	pthread_join(pclient, NULL);

	return 0;
}
