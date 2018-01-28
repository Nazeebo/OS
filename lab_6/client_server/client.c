#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  int fd;
  char* myfifo = "./tmp/newfifo";
  char buf[255];
  scanf("%s",buf);
  //fgets(buf,sizeof(buf),stdin);
  mkfifo(myfifo, 0666);
  fd = open(myfifo, O_CREAT|O_TRUNC, O_WRONLY);
  write(fd, buf, sizeof(buf));
  close(fd);
  unlink(myfifo);
  return 0;
}
