#include "windows.h"
#include "stdio.h"

int main(int argc, char** argv)
{
    for (int i = 1; i < 15; ++i) {
        printf("\\\\\\\\Grandhild process named %s with parent %s is on step - %d\n", argv[1], argv[0], i);
        Sleep(2500);
    }

    return 0;

}