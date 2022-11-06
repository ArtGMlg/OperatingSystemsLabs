#include "stdio.h"
#include "fcntl.h"
#include "string.h"

void main(){
    FILE * f = fopen("output.txt", "w");
    char text[50] = {};
    fgets(text, 50, stdin);
    fwrite(text, 1, strlen(text), f);
    fclose(f);
}