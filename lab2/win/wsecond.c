#include "stdio.h"
#include "windows.h"
#include "handleapi.h"

void main(){
    LARGE_INTEGER liMoveTo;
    LARGE_INTEGER liNewLocation;
    HANDLE finhandle1 = CreateFile("output.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE finhandle2;
    DuplicateHandle(GetCurrentProcess(), finhandle1, GetCurrentProcess(), &finhandle2, 0, FALSE, DUPLICATE_SAME_ACCESS);
    HANDLE finhandle3 = CreateFile("output.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    // liMoveTo.QuadPart = 10 * sizeof(TCHAR);
    SetFilePointer(finhandle1, 10, NULL, FILE_BEGIN);
    printf("finhandle1: %d\n", finhandle1);
    printf("finhandle2: %d\n", finhandle2);
    printf("finhandle3: %d\n", finhandle3);
    char buf[8];
    ReadFile(finhandle1, buf, 7, NULL, NULL);
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buf, 7, NULL, NULL);
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), "\n", 1, NULL, NULL);
    memset(buf, 0, 7);
    ReadFile(finhandle2, buf, 7, NULL, NULL);
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buf, 7, NULL, NULL);
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), "\n", 1, NULL, NULL);
    memset(buf, 0, 7);
    ReadFile(finhandle3, buf, 7, NULL, NULL);
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buf, 7, NULL, NULL);
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), "\n", 1, NULL, NULL);
    CloseHandle(finhandle1);
    CloseHandle(finhandle2);
    CloseHandle(finhandle3);
}