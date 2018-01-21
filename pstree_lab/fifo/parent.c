#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd, status;
    char* myfifo = "/tmp/newfifo";
    char buf[255];
    pid_t cpid = fork(); //creating child process
    if (cpid) { //parent
        fd = open(myfifo, O_RDONLY);
        wait(&status);
        read(fd, buf, sizeof(buf));
        printf("%s\n",buf);
        close(fd);
    }
    else //child
      execl("child.out","child.out",(char*)NULL);
    return 0;
}
