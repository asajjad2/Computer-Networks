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
	char buffer[MAXLINE];
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
	
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
	
	int len, n, isServer = 5;

	len = sizeof(cliaddr); //len is value/resuslt

	printf("\t\tSERVER-SIDE\t\t\n");

    while(isServer){
        
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, ( struct sockaddr *) &cliaddr, &len);

        //check palindrome
        int i, j, flag = 0;
        for(i = 0, j = n - 2; i < j; i++, j--){

            if(buffer[i] != buffer[j]){
                flag = 1;
                break;
            }
        }

        buffer[n] = '\0';
        char true[] = "Is Palindrome";
        char false[] = "Is Not Palindrome";

        if(flag == 0){
            
            printf("Client : %sServer : ", buffer);
            printf("Is Palindrome\n");
            sendto(sockfd, (const char *)true, strlen(true), 0, (const struct sockaddr *) &cliaddr, len);

        }
        else{

            printf("Client : %sServer : ", buffer);
            printf("Is Not Palindrome\n");
            sendto(sockfd, (const char *)false, strlen(false), 0, (const struct sockaddr *) &cliaddr, len);

        }

        isServer--;
    }

	
	
	
	
	return 0;
}
