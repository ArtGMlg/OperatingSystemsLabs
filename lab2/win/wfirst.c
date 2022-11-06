#include "stdio.h"
#include "fcntl.h"
#include "string.h"
#include "windows.h"

void main(){
    HANDLE hFile = CreateFile("output.txt", GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    char text[50] = {};
    ReadFile(GetStdHandle(STD_INPUT_HANDLE), text, 50, NULL, NULL);
    WriteFile(hFile, text, 50, 0, NULL);
    CloseHandle(hFile);
}