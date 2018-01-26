#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void quickSort(char **book, int left, int right) {
    srand(time(NULL));
    if (left >= right) return;
    int i = left, j = right;
    char p[30];
    strcpy(p, book[left + rand() % (right - left)]);

    while (i <= j) {
        while (strcmp(book[i], p) < 0)i++;
        while (strcmp(book[j], p) > 0)j--;
        if (i <= j) {
            char tmp[30];
            strcpy(tmp, book[i]);
            strcpy(book[i], book[j]);
            strcpy(book[j], tmp);
            i++;
            j--;
        }
    }

    if (left < j) quickSort(book, left, j);
    if (i < right) quickSort(book, i, right);
};

int main(int argc, char *argv[]) {
    FILE *fd = fopen("input.txt", "r");
    FILE *out = fopen("sorted.txt", "w");
    int i, j, count = 0;
    char **arr = malloc(5000000 * sizeof(char *));
    for (i = 0; i < 5000000; i++)
        arr[i] = malloc(30 * sizeof(char));
    char buf[101];

    while (fscanf(fd, "%s", buf) > 0) {
        int str_len = strlen(buf) - 1;
        int last_symbol = (int) buf[str_len];
        if (last_symbol < 65 || last_symbol > 122 ||
            (last_symbol > 90 && last_symbol < 97))   //A - 65, Z - 90, a - 97, z - 122
            buf[str_len] = 0;
        //printf("%s ",buf);
        strcpy(arr[count], buf);
        count++;
    }
    fclose(fd);
    //printf("\n\n");
    quickSort(arr, 0, count - 1);

    for (i = 0; i < count; i++)
        fprintf(out,"%s ", arr[i]); 
    fclose(out);

    return 0;

}

/*    for(i = 0; i<count-1;i++)
        for(j = i+1; j <count;j++)
            if(strcmp(arr[i],arr[j]) > 0){
                char tmp[30];
                strcpy(tmp,arr[i]);
                strcpy(arr[i],arr[j]);
                strcpy(arr[j],tmp);
            }*/
