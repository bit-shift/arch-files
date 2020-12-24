#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

#define BUFMAX 2048
int PORT;

void server();
char *get_line(char *buffer);
char *get_file_name(char *line);
char *get_file_contents(char *name);
char *http_response(char *contents);

int main (int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: ./WebServer port\n");
		exit(EXIT_FAILURE);
	}
	PORT = strtol(argv[1], NULL, 10);
	server();
	return 0;
}

void server() {
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFMAX];
	char *first;
	//char *hello = "Hello from server";

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

	while (1) {
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
			fprintf(stderr, "Accept failed.\n");
			exit(EXIT_FAILURE);
		}

		valread = read(new_socket, buffer, BUFMAX);
		first = get_line(buffer);
		if (first == NULL) {
			printf("error.\n");
		}
		send(new_socket, first, strlen(first), 0);
		//printf("%s\n", first);
		close(new_socket);
	}

}

char *get_line(char *buffer) {
	char first_line[BUFMAX];
	char *ret;
	char c;
	int i = 0;
	c = buffer[i];
	while (c != '\r') {
		first_line[i] = c;
		i++;
		c = buffer[i];
	}
	first_line[i] = '\0';
	ret = get_file_name((char *) first_line);
	return ret;
}

char *get_file_name(char *line) {
	char *token, *ret;
	token = strtok(line, " ");
	token = strtok(NULL, " ");

	ret = get_file_contents(token);

	return ret;
}

char *get_file_contents(char *name) {
	long numbytes;
	char *buffer, *ret;
	FILE *infile;

	memmove(name, name + 1, strlen(name));
	infile = fopen(name, "rb");

	if (infile == NULL) {
		ret = http_response(NULL);
	}
	else {
		fseek(infile, 0L, SEEK_END);
		numbytes = ftell(infile);
		fseek(infile, 0L, SEEK_SET);	
		buffer = (char *) calloc(numbytes, sizeof(char));	

		if(buffer == NULL) {
			fprintf(stderr, "Memory failure.\n");
			exit(EXIT_FAILURE);
		}

		fread(buffer, sizeof(char), numbytes, infile);
		fclose(infile);

		ret = http_response(buffer);
	}

	return ret;
}

char *http_response(char *contents) {
	char *ret;
	if (contents == NULL) {
		char response[BUFMAX];
		sprintf(response, "HTTP/1.1 404 Not Found\r\n\r\n");
		ret = (char *) response;
	}
	else {
		int len = strlen(contents);
		char response[BUFMAX+len];
		sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", contents);
		ret = (char *) response;
	}
	return ret;
}
