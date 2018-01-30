#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_BUF 1024

int main(int argc, char* argv[]){
  if(argc < 2) return 0;

    struct hostent *h;
    h = gethostbyname(argv[1]);

    if(NULL == h){
      printf("Incorrect hostname\n");
      return 0;
    }

    if(h->h_addrtype != AF_INET){ //if it's now an IPv4 adress
      printf("Address of host isn't IPv4\n");
      return 0;
    }

    struct sockaddr_in local;
    inet_aton("127.0.0.1",&local.sin_addr);
    local.sin_port=htons(3000);
    local.sin_family = AF_INET;
    int s= socket(AF_INET,SOCK_STREAM,0);
    connect(s,(struct sockaddr*) &local, sizeof(local));

    char buf[MAX_BUF],msg[MAX_BUF];

    read(s, msg, MAX_BUF);
    int pid = atoi(msg);

    int i=0;
    while(NULL != h->h_addr_list[i]){
      struct in_addr* tmp = (struct in_addr*) h->h_addr_list[i]; //convert to IPv4 explanation
      strcpy(buf,argv[1]);
      strcat(buf," ");
      strcat(buf,inet_ntoa(*tmp));
      write(s,buf,strlen(buf)+1);  //convert to human readable format
      //printf("%s\n",buf);
      i++;
    }



    if(argv[2])
      kill(pid,SIGTERM);

    close(s);

    return 0;
}
