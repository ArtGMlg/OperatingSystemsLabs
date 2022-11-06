#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void main()
{
    int o, fd;
    FILE *file;
    file = fopen("myfile.txt", "r");
    fd = open("myfile.txt", O_RDWR);
    errno = 0;
    o = lockf(fd, F_TLOCK, 0);
    if (o != -1)
    {
        printf("file locked\n");
        char buf[30];
        fgets(buf, 30, file);
        printf(buf);
        getchar();
        o = lockf(fd, F_ULOCK,0);
        printf("file unlocked\n");
    }
    else
    {
        printf("unable to lock file\n");
        printf(strerror(errno));
        getchar();
        o = lockf(fd, F_ULOCK,0);
    }
    fclose(file);
}
