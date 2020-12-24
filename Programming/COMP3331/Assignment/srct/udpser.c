#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define MAXLINE 1024
sem_t wait1, wait2;
int PORT, C_PORT;

struct Request {
	int sock;
	struct sockaddr_in cliaddr;
	char *msg;
	socklen_t len;
};


void *handle_send(void *varg) {
	struct Request *req = (struct Request *)varg;

	sendto(req->sock, (const char *)req->msg, strlen(req->msg), MSG_CONFIRM, (const struct sockaddr *) &(req->cliaddr), req->len); 
	printf("Hello message sent by server.\n"); 
	sem_post(&wait2);

	return NULL;
}

void *server (void *varg) {
	int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from server"; 
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 

    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
     
    int n, rc;
	pthread_t threads[20];
	int thread_no = 0;
	socklen_t len;

	while (1) {
		sem_wait(&wait1);
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len); 
		buffer[n] = '\0'; 
		printf("Client : %s\n", buffer); 
		struct Request *req = malloc(sizeof(struct Request)); 
		req->cliaddr = cliaddr;
		req->sock = sockfd;
		req->len = len;
		req->msg = hello;

		rc = pthread_create(&threads[thread_no], NULL, handle_send, (void *) req);
		thread_no++;

	}
}	

void *client (void *varg) {
	int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from client"; 
    struct sockaddr_in servaddr; 
  
    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 

	struct timeval read_timeout;
	read_timeout.tv_sec = 10;
	read_timeout.tv_usec = 10;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof(read_timeout));
 
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(C_PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    int n;
	socklen_t len;
    
    sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
    printf("Hello message sent by client.\n"); 
	sem_post(&wait1);
	sem_wait(&wait2);

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
	printf("Read %d bytes\n", n);
	fflush(stdout);
    buffer[n] = '\0'; 
    printf("Server : %s\n", buffer); 
  
    close(sockfd); 

	return NULL;
}

int main(int argc, char *argv[]) { 
	int pserver, pclient;
	pthread_t p, c;

	PORT = strtol(argv[1], NULL, 10);
	C_PORT = strtol(argv[2], NULL, 10);
	sem_init(&wait1, 0, 0);
	sem_init(&wait2, 0, 0);

	pserver = pthread_create(&p, NULL, server, NULL);
	sleep(10);
	pclient = pthread_create(&c, NULL, client, NULL);

	pthread_join(c, NULL);
	pthread_join(p, NULL);
	sem_destroy(&wait1);
	sem_destroy(&wait2);
	
    return 0; 
} 
