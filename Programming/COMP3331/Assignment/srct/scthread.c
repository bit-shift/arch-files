#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include "scthread.h"

#define PORT 50000

int main (int argc, char *argv[]) {
	int pclient, pserver;
	pthread_t cthread_id, sthread_id;

	pclient = pthread_create(&cthread_id, NULL, client, NULL);
	if (pclient != 0) {
		fprintf(stderr, "Failed to create client thread.\n");
	}

	pserver = pthread_create(&sthread_id, NULL, server, NULL);
	if (pserver != 0) {
		fprintf(stderr, "Failed to create server thread.\n");
	}

	pthread_join(cthread_id, NULL);
	pthread_join(sthread_id, NULL);

	return 0;
}

void *server(void *varg) {
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello from server";

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		fprintf(stderr, "Socket failed.\n");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		fprintf(stderr, "Setsockopt failed.\n");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		fprintf(stderr, "Bind failed.\n");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0) {
		fprintf(stderr, "Listen failed.\n");
		exit(EXIT_FAILURE);
	}

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
		fprintf(stderr, "Accept failed.\n");
		exit(EXIT_FAILURE);
	}

	valread = read(new_socket, buffer, 1024);
	printf("%s\n", buffer);
	send(new_socket, hello, strlen(hello), 0);
	printf("Hello message sent by server.\n");

	return NULL;
}

void *client(void *varg) {
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        fprintf(stderr, "Socket creation error.\n"); 
        exit(EXIT_FAILURE);
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)  { 
        fprintf(stderr, "Invalid address/ Address not supported.\n"); 
        exit(EXIT_FAILURE);
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
        fprintf(stderr, "Connection Failed.\n"); 
		exit(EXIT_FAILURE);
    } 

    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent by client.\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n", buffer); 

    return NULL; 
}
