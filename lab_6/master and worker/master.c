#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int status;
    pid_t cpid = fork(); //creating child process
    if (cpid) { //parent
        FILE* fd = fopen("jokes.txt","r");
        char buf[255], jokes[10][255];
        int count = 0, i;
        while(fgets(buf, 255, fd) > 0){
            strcpy(jokes[count], buf);
            count++;
        }
        fclose(fd);
        srand(time(NULL));
        for(i = 0; i < 6; i++){
        	printf("%s/n",jokes[rand() % 6]);
        	sleep(0.5);
		}
        wait(&status);
        printf("%s","worker finished his job, the result lies in sorted.txt");
        exit(0);
    }
    else //child
      execl("worker.out","worker.out",(char*)NULL);
    return 0;
}
