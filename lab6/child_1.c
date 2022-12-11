#include "windows.h"
#include "stdio.h"

int main(int argc, char** argv)
{
    STARTUPINFO info = { sizeof(info) };
    PROCESS_INFORMATION processInfo;
    char* childName = "a";
    char* buf = (char*)malloc(strlen(argv[0]) + strlen(childName) + 1);

    sprintf(buf, "%s %s", argv[0], childName);

    if (!CreateProcess("GrandChild_1.exe", buf, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
    {
        return 0;
    }

    for (int i = 1;; ++i) {
        printf("\\\\Child process named %s is on step %d\n", argv[0], i);
        Sleep(2500);
    }

    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    return 0;
}