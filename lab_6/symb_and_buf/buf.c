#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd = open ("output.txt",O_WRONLY);
    char abc[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    srand(time(NULL));
    int i,j,wut;
    unsigned int start_time = clock();
    for(i = 0; i < 200; i++) {
        char buf[1000010];
        for (j = 0; j < 1000000; j++)  //200 000 000 ~ 195mb
            buf[j]=abc[rand() % 26];
        wut = write(fd, buf, strlen(buf)+1);
    }
    write(fd,"Why it isn't working",sizeof("Why it isn't working"));
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    printf("%lf \n",search_time/1000.0);
    printf("%d\n",wut);
    close(fd);
    return 0;
}
