#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <signal.h>

#define MAX_BUF 1024

int main(){
  FILE* file = fopen("output.txt","w");

  struct sockaddr_in local,incoming;
  inet_aton("127.0.0.1",&local.sin_addr);
  local.sin_port=htons(3000);
  local.sin_family=AF_INET;
  int s= socket(AF_INET,SOCK_STREAM,0);
  bind(s,(struct sockaddr*) &local, sizeof(local));
  listen(s,5);
  socklen_t in_len = sizeof(incoming);

  int	cs=accept(s, (struct sockaddr*)&incoming, &in_len);
  int pid = getpid();
  write(cs, &pid, sizeof(int));

  while(1){
    char buf[MAX_BUF];
    read(cs,buf,MAX_BUF);
    fprintf(file,"%s\n",buf);
    close(cs);
  }

  return 0;
}
