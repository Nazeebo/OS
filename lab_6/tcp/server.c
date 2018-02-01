#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <signal.h>
#include <sys/types.h>
#define MAX_BUF 1024

int main(){
    FILE* file = fopen("output.txt","w");
    struct sockaddr_in server,incoming;

    //Create socket
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if (sock == -1){
        printf("Could not create socket\n");
    }
    printf("Socket created\n");

    //Prepare the sockaddr_in structure
    server.sin_port=htons(8888);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family=AF_INET;
    
    //Bind
    if( bind(sock,(struct sockaddr *)&server , sizeof(server)) < 0){
        //print the error message
        perror("bind failed. Error\n");
        return 1;
    }
    printf("bind done\n");

    //Listen
    listen(sock,5);

    //Accept and incoming connection	
    printf("Waiting for incoming connections...\n");
    int c = sizeof(incoming);

    //accept connection from an incoming client
    while(1){
        //printf("Entered the cycle\n");
        int client_sock=accept(sock, (struct sockaddr*)&incoming, (socklen_t*)&c);
        if (client_sock < 0){
            perror("accept failed");
            return 1;
        }
        printf("Connection accepted\n");

        //Receive a message from client
        char buf[MAX_BUF];
        read(client_sock,buf,MAX_BUF);
        //int bytes_read = recv(client_sock,buf,2048,0);
        printf("got message: %s\n",buf);
        printf("printed in output symbols: %d\n",fputs(buf,file));
        fclose(file);
        close(client_sock);
  }

  return 0;
}
