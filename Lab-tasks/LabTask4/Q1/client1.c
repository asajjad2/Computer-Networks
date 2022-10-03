// 172.17.141.99



#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char**argv)
{
   int sockfd,n;
   struct sockaddr_in servaddr;
   char * sendline;
   sendline = "hellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellolohellohellohellohellohellohellohellohellohellolohellohellohellohellohellohellohellohellohellolohellohellohellohellohellohellohellohellohellolo\r\n";

   sockfd=socket(AF_INET,SOCK_STREAM,0);

   memset(&servaddr, 0, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=inet_addr("172.17.141.99");
   servaddr.sin_port=htons(8018);

    int connect_status = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("%d\n", connect_status);

    int send_status = send(sockfd,sendline,strlen(sendline),0);
    printf("%d\n", send_status);

    printf("END\n");
    return 0;
}