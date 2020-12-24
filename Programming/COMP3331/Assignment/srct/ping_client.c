// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     8080 
#define MAXLINE 1024 
sem_t mutex;
sem_t sersync;
  
void *client (void *varg) {
    int sockfd;
   	int *client = (int *)varg;	
    //char buffer[MAXLINE]; 
    char hello[MAXLINE];
    struct sockaddr_in     servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    //int n; 
	//socklen_t len;
	for (int i = 0; i < 10; i++) {
		sprintf(hello, "PING %d from %d", i, *client);
		//sem_wait(&mutex);
		sendto(sockfd, (const char *)hello, strlen(hello), 
			MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
				sizeof(servaddr)); 
		//printf("Hello message sent.\n"); 
		//sem_post(&sersync);
		//sleep(1);
		//sem_wait(&sersync);
			  
		//n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
		//buffer[n] = '\0';
		//printf("Server : %s\n", buffer);
		//sem_post(&mutex);
	}

	return NULL;
}

void *server (void *varg) {
	int sockfd; 
    char buffer[MAXLINE]; 
    //char *hello = "Response received"; 
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    int n; 
	socklen_t len;
	while (1) {
		//sem_wait(&sersync);
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
					MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
					&len); 
		buffer[n] = '\0'; 
		printf("Client : %s\n", buffer); 
		//sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
		//sem_post(&sersync);
		//printf("Hello message sent.\n");  
	}
    return NULL;
}	


// Driver code 
int main() { 
	sem_init(&mutex, 0, 1);
	sem_init(&sersync, 0, 0);

	int pclient_0, pserver;
	pthread_t c_0, p_0;

	int c0 = 0;
	//int c1 = 1;

	pserver = pthread_create(&p_0, NULL, server, NULL);

	pclient_0 = pthread_create(&c_0, NULL, client, (void *)&c0);
	//pclient_1 = pthread_create(&c_1, NULL, client, (void *)&c1);

	pthread_join(c_0, NULL);
	//pthread_join(c_1, NULL);
	pthread_join(p_0, NULL);
	sem_destroy(&mutex);
	sem_destroy(&sersync);
    return 0; 
} 

/*
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 50000

int main () {
	int client_fd, n_rec;
	socklen_t len;
	char bufsend[1024];
	char bufrec[1024];
	sprintf(bufsend, "PING request from client");
	struct sockaddr_in server_addr;
	
	//for (int i = 0; i < 2; i++) {
		if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			fprintf(stderr, "Socket failed - client UDP.\n");
			exit(EXIT_FAILURE);
		}

		memset(&server_addr, '0', sizeof(server_addr));

		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = INADDR_ANY;
		server_addr.sin_port = htons(PORT);

		sendto(client_fd, (char *)bufsend, 1024, MSG_CONFIRM, (struct sockaddr *)&server_addr, sizeof(server_addr));

		n_rec = recvfrom(client_fd, (char *)bufrec, 1024, MSG_WAITALL, (struct sockaddr *) &server_addr, &len); 

    	bufrec[n_rec] = '\0'; 
		printf("%s\n", bufrec);

		close(client_fd);
	//}

	return 0;
}
*/
