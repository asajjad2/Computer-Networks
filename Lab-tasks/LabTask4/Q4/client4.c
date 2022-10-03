#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include <netinet/in.h>


int main() {
	
	char request[256] = "Hello I am Client are you there";
	char buf[200];
	
	// create the socket
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	//setup an address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(3001);

	connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));
	
	
        int n = recv(sock, &buf, sizeof(buf), 0);
        buf[n] = '\0';
        printf("%s\n", buf);
        fgets(buf, 200, stdin);

        send(sock, buf, sizeof(buf), 0);
        
        if(buf[0] == '1'){
            memset(buf, 0, sizeof buf);
            n = recv(sock, &buf, sizeof(buf), 0);
            buf[n] = '\0';
            printf("\n%s", buf);
            fgets(buf, 200, stdin);
            send(sock, buf, sizeof(buf), 0);
            n = recv(sock, &buf, sizeof(buf), 0);
            buf[n] = '\0';
            printf("\n%s", buf);
        }
        else if(buf[0] == '2'){
            recv(sock, &buf, sizeof(buf), 0);
            printf("\n%s\n", buf);
            fgets(buf, 200, stdin);
            send(sock, buf, sizeof(buf), 0);
            recv(sock, &buf, sizeof(buf), 0);
            printf("\n%s", buf);
        }
        else if(buf[0] == '3'){
            printf("Exiting...\n");
            // break;
        }
    
	

	close(sock);

	return 0;
}
