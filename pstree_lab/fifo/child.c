#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int getPpid(int pid) {   //getting ppid of process with given pid
    char fname[40],buf[100];
    char* myfifo = "/tmp/newfifo";
    sprintf(fname, "/proc/%d/status", pid);
    FILE *f = fopen(fname, "r");
    int ppid;
    while (fgets(buf, sizeof(buf), f)) {
        char tag[255];
        ppid = -1;
        sscanf(buf, "%s\t%i", tag, &ppid);
        if (strcmp(tag, "PPid:") == 0)
            break;
    }
    fclose(f);
    return ppid;
}

int main(int argc, char *argv[]) {
  int fd;
  char* myfifo = "/tmp/newfifo";
  int pid = getpid();
  int ppid, count = 0, treeInPid[100];
  printf("%d ",pid);
  treeInPid[count] = pid;
  while (ppid != 1) {
       ppid = getPpid(pid);
       int inf = ppid;
       treeInPid[++count] = inf;
       pid = ppid;
       printf("%d ",ppid);
  }
  char tree[255];
  for(int i = count; i>=0; i--){
    char fname[40],buf[100];
    sprintf(fname, "/proc/%d/status", treeInPid[i]);
    FILE *f = fopen(fname, "r");
    fgets(buf, sizeof(buf), f);
    char tag[255],name[100];
    sscanf(buf, "%s\t%s", tag, name);
    strcat(tree,name);
    if(i != 0) strcat(tree,"-");
    fclose(f);
  }
  mkfifo(myfifo, 0666);
  fd = open(myfifo, O_WRONLY);
  write(fd, tree, sizeof(tree));
  close(fd);
  unlink(myfifo);
  return 0;

}
