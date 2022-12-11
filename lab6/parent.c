#include "windows.h"
#include "stdio.h"

int main()
{
    STARTUPINFO info = { sizeof(info) };

    PROCESS_INFORMATION processInfo1, processInfo2;

    HANDLE hJob = CreateJobObject(NULL, NULL);

    if (!CreateProcess("Child_1.exe", "A", NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo1))
    {
        return 0;
    }

    if (!CreateProcess("Child_2.exe", "B", NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo2))
    {
        return 0;
    }

    AssignProcessToJobObject(hJob, processInfo2.hProcess);

    for (int i = 1; i <= 15; ++i) {
        printf("\nParent process is now on step %d\n", i);
        if (i == 7) {
            TerminateProcess(processInfo1.hProcess, 0);
            printf("Child process named A is completed on step %d\n\n", i);
        }

        if (i == 11) {
            TerminateJobObject(hJob, 0);
            printf("Child process named B is completed on step %d\n\n", i);
        }

        Sleep(2500);

    }

    CloseHandle(processInfo1.hProcess);

    CloseHandle(processInfo1.hThread);

    CloseHandle(processInfo2.hProcess);

    CloseHandle(processInfo2.hThread);

    return 0;

}