#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

/*char* make_filename(int pid){
    char* filename= malloc (sizeof(char)*30);
    sprintf(filename, "/proc/%d/status", id);
    return filename;
}*/

int getPpid(int pid) {   //getting ppid of process with given pid
    char fname[40],buf[100];
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
    int pipefd[2];
    int status;
    pipe(pipefd); //openning pipe
    pid_t cpid = fork(); //creating child process
    if (cpid) { //parent
        close(pipefd[1]);
        int info,count;
        char buf[100];
        wait(&status);
        read(pipefd[0],buf, sizeof(buf));
        printf("%s\n",buf);
        close(pipefd[0]);
    }
    else { //child
        close(pipefd[0]);
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
        //printf("%s",tree);
        write(pipefd[1], tree, sizeof(tree));
        close(pipefd[1]);
        exit(0);
    }
    return 0;
}
