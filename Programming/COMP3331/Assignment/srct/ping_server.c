// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     8080 
#define MAXLINE 1024 
  
// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Response received"; 
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
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
					MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
					&len); 
		buffer[n] = '\0'; 
		printf("Client : %s\n", buffer); 
		sendto(sockfd, (const char *)hello, strlen(hello),  
			MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
				len); 
		//printf("Hello message sent.\n");  
	}
    return 0; 
} 

/*
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 50000

int main () {
	int server_fd;
	char bufrec[1024];
	char bufsend[1024];
	sprintf(bufsend, "PING response from server.");
	struct sockaddr_in client_addr, server_addr;

	if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "Socket failed - server UDP.\n");
		exit(EXIT_FAILURE);
	}

	memset(&server_addr, '0', sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		fprintf(stderr, "Bind failed - server UDP.\n");
		exit(EXIT_FAILURE);
	}

	int n_rec;
	socklen_t size_cli;
		memset(&client_addr, '0', sizeof(client_addr));

		n_rec = recvfrom(server_fd, (char *)bufrec, 1024, MSG_WAITALL, (struct sockaddr *)&client_addr, &size_cli);

		bufrec[n_rec] = '\0';
		printf("%s\n", bufrec);
		sendto(server_fd, (char *)bufsend, 1024, MSG_CONFIRM, (struct sockaddr *) &client_addr, size_cli);

	return 0;
}
*/
