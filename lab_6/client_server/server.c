#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int main(int argc, char *argv[]) {
  int fd,i;
  char* myfifo = "./tmp/newfifo";
  char buf[255];
  fd = open(myfifo, O_RDONLY, 0666);
  read(fd, buf, sizeof(buf));
  for(i = 0; i < 10; i++)
    printf("%s\n", buf);
  close(fd);
  unlink(myfifo);
  return 0;
}
