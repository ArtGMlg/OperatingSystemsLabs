#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"

void main(){
    FILE * fin1 = fopen("output.txt", "r");
    int finhandle1 = fileno(fin1);
    int finhandle2 = dup(finhandle1);
    FILE * fin2 = fopen("output.txt", "r");
    int finhandle3 = fileno(fin2);

    fseek(fin1, 10, 0);
    printf("finhandle1: %i\n", finhandle1);
    printf("finhandle2: %i\n", finhandle2);
    printf("finhandle3: %i\n", finhandle3);
    char buf[7] = {};
    read(finhandle1, buf, 7);
    fputs(buf, stdout);
    printf("\n");
    memset(buf, 0, 7);
    read(finhandle2, buf, 7);
    fputs(buf, stdout);
    printf("\n");
    memset(buf, 0, 7);
    read(finhandle3, buf, 7);
    fputs(buf, stdout);
    printf("\n");
    memset(buf, 0, 7);
    fclose(fin1);
    fclose(fin2);
}