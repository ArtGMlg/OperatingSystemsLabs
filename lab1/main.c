#include "stdio.h"
#include "windows.h"

int main(){
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE herr = GetStdHandle(STD_ERROR_HANDLE);

    printf("STD_INPUT_HANDLE=%d\n", hin);
    printf("STD_OTPUT_HANDLE=%d\n", hout);
    printf("STD_ERROR_HANDLE=%d\n", herr);

    char strout[] = "Type something: \n";
    char strin[100];

    WriteFile(hout, strout, strlen(strout), NULL, NULL);

    ReadFile(hin, strin, 100, NULL, NULL);

    printf("%s", strin);
}