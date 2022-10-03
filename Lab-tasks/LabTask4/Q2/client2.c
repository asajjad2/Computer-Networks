
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 1024
int main(){
    
    int sock = socket(AF_INET,SOCK_STREAM,0);   //Creating Socket

    //Setup up address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(3001);
    //connecting
    connect(sock,(struct sockaddr*) &server_address,sizeof(server_address));
    //Sending 

    while(1){
        char buff[MAXLINE];
        char Message[MAXLINE];
        pid_t receivingProcess = fork();
        if(receivingProcess == 0){
            int n=recv(sock,buff,sizeof(buff),0);
            buff[n]='\0';
            printf("Server : %s \n",buff);
        }
        else{
            fgets(Message,MAXLINE,stdin);
            send(sock, Message,strlen(Message),0);
            
            
        }
    }
    close(sock);

    return 0;


}
