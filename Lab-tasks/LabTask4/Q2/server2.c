#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#define MAXLINE 1024
int main(){

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    //Setup up server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(3001);

    //Binding
    bind(server_socket,(struct sockaddr*) &server_address,sizeof(server_address));
    listen(server_socket,5);
    int client_socket = accept(server_socket,NULL,NULL);
    while (1)
    {
	        char buf[MAXLINE];
            char server_message[MAXLINE];

        pid_t receivingProcess = fork();
        if(receivingProcess == 0){
            int n=recv(client_socket, &buf, sizeof(buf), 0);
            buf[n]='\0';
            printf("Server : %s\n", buf);
        }
        else{
            fgets(server_message,MAXLINE,stdin);
            send(client_socket, server_message, strlen(server_message), 0);
        }
    }
    close(server_socket);
    
    

    return 0;

}