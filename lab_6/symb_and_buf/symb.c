#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE* f = fopen("output.txt","w");
    char abc[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    srand(time(NULL));
    int i;
    unsigned int start_time =  clock();
    for(i = 0; i < 200000000; i++) {  //200 000 000 ~ 195mb
        fprintf(f, "%c", abc[rand() % 26]);
    }
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    printf("%lf \n",search_time/1000.0);
    fclose(f);
    return 0;
}
