// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 8080
#define MAXLINE 1024

// Driver code
int main() {
	int sockfd;
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr1, cliaddr2;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	//memset(&servaddr, 0, sizeof(servaddr));
	//memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	int len1, len2, n1, n2;

	len1 = sizeof(cliaddr1); //len is value/resuslt
	len2 = sizeof(cliaddr2); //len is value/resuslt

	printf("\t\tSERVER-SIDE\t\t\n");

    while(1){
		char buffer1[MAXLINE], buffer2[MAXLINE];
		printf("abc");

        n1 = recvfrom(sockfd, (char *)buffer1, MAXLINE, 0, ( struct sockaddr *) &cliaddr1, &len1);
        buffer1[n1] = '\0';
        printf("Client-1 : (%d Bytes) - %s", n1, buffer1);

        sendto(sockfd, (const char *)buffer1, strlen(buffer1), 0, (const struct sockaddr *) &cliaddr2, len2);

		n2 = recvfrom(sockfd, (char *)buffer2, MAXLINE, 0, ( struct sockaddr *) &cliaddr2, &len2);

		buffer2[n2] = '\0';
        printf("Client-2 : (%d Bytes) - %s", n2, buffer2);

		sendto(sockfd, (const char *)buffer2, strlen(buffer2), 0, (const struct sockaddr *) &cliaddr1, len1);
    }

	
	
	
	
	return 0;
}