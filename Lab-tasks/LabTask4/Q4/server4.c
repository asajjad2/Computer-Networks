#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int isPrimeNumber(int n){
    int i;
    for(i=2; i<n; i++){
        if(n%i == 0){
            return 0;
        }
    }
    return 1;
}

char* reverseString(char* str){
    int i, j;
    char temp;
    for(i=0, j=strlen(str)-1; i<j; i++, j--){
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    return str;
}

int main() {

	char server_message[256] = "Menu\n1. Check number is prime\n2. Reverse string\n3. Exit\n";
	char buf[200];
	// create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	
	// define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(3001);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	listen(server_socket, 5);
	printf("\t\tSERVER-SIDE\t\t\n");

    while(1){

        int client_socket;
        client_socket = accept(server_socket, NULL, NULL);

        pid_t pid = fork();

        if(pid == 0){
            
            printf("\n\t\tCHILD-PROCESS\t\t\n");

            
            send(client_socket, server_message, strlen(server_message), 0);
            memset(server_message, 0, strlen(server_message));
            int n = recv(client_socket, &buf, sizeof(buf), 0);
            buf[n] = '\0';
            printf("\n%s\n", buf);

            if(buf[0] == '1'){

                char message[256] = "Enter a number: ";
                strcpy(server_message, message);
                send(client_socket, server_message, strlen(server_message), 0);
                memset(server_message, 0, strlen(server_message));
                n = recv(client_socket, &buf, sizeof(buf), 0);
                buf[n] = '\0';
                printf("\n%s\n", buf);

                int num = atoi(buf);
                if(isPrimeNumber(num)){
                    char message[256] = "Number is prime\n";
                    strcpy(server_message, message);
                    send(client_socket, server_message, strlen(server_message), 0);
                    memset(server_message, 0, strlen(server_message));
                }
                else{
                    char message[256] = "Number is not prime\n";
                    strcpy(server_message, message);
                    send(client_socket, server_message, strlen(server_message), 0);
                    memset(server_message, 0, strlen(server_message));
                }

            }
            else if(buf[0] == '2'){

                printf("Reverse string\n");
                char message[256] = "Enter a string: ";
                strcpy(server_message, message);
                send(client_socket, server_message, strlen(server_message), 0);
                memset(server_message, 0, strlen(server_message));
                n = recv(client_socket, &buf, sizeof(buf), 0);
                buf[n] = '\0';

                strcpy(server_message, reverseString(buf));
                send(client_socket, server_message, strlen(server_message), 0);
                memset(server_message, 0, strlen(server_message));
            }
            else if(buf[0] == '3'){
                // break;
            }
            else{
                printf("Invalid input\n");
            }
            
            
            close(client_socket);

        } else {

        }
      
        
    }

	
	
	return 0;
}