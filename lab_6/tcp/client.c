#include <netdb.h>
#include <stdio.h>  //printf
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h>  //socket
#include <unistd.h>
#include <string.h>  //strlen
#include <stdlib.h>
#include <signal.h>  //kill
#include <sys/types.h>
#define MAX_BUF 1024

int main(int argc, char* argv[]){
  if(argc < 3) return 0;

    struct hostent *h;
    h = gethostbyname(argv[1]);

    if(NULL == h){
      printf("Incorrect hostname\n");
      return 0;
    }

    if(h->h_addrtype != AF_INET){ //if it's not an IPv4 adress
      printf("Address of host isn't IPv4\n");
      return 0;
    }

    struct sockaddr_in local;
    char message[255];

    //Create socket
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if (sock == -1){
        printf("Could not create socket\n");
    }
    printf("Socket created\n");

    local.sin_addr.s_addr = inet_addr("127.0.0.1");
    local.sin_port=htons(8888);
    local.sin_family = AF_INET;

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&local , sizeof(local)) < 0){
        perror("connect failed. Error\n");
        return 1;
    }

    printf("Connected\n");

    struct in_addr* tmp = (struct in_addr*) h->h_addr_list[0]; //convert to IPv4 explanation
    strcpy(message, argv[1]);
    strcat(message, " ");
    strcat(message, inet_ntoa(*tmp));
    printf("Sending %d symbols to the server \n",write(sock, message, strlen(message)+1));  //convert to human readable format
    //send(sock, message, sizeof(buf),0);

    int pid = atoi(argv[2]);

    printf("2 seconds preparation before assassination \n");
    sleep(2);
    
    kill(pid,SIGTERM);
    printf("Target is  killed, my job here is done\n");
    close(sock);

    return 0;
}
