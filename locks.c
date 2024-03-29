#include "common.h"
#define FILE_NAME "locks.c"

void locks()
{
    struct flock fl = {
        .l_type = F_WRLCK,
        .l_whence = SEEK_SET,
        .l_start = 0,
        .l_len = 0,
        .l_pid = 0,
    };

    int fd;

    fd = open(FILE_NAME, O_RDWR);

    printf("PARENT: Trying to get a write lock to the file\n");
    fcntl(fd, F_SETLKW, &fl);
    printf("PARENT: Got the lock\n");

    pid_t pid = fork();
    if (pid == 0)
    {
        fl.l_type = F_RDLCK;

        printf("CHILD: Checking who has the lock:\n");
        fcntl(fd, F_GETLK, &fl);
        printf("CHILD: Lock owner PID: %d, Parent PID: %d\n", fl.l_pid, getppid());

        printf("CHILD: Blocking until I get a read lock to the file\n");
        fcntl(fd, F_SETLKW, &fl);

        printf("CHILD: Got the lock, can exit now\n");
        fflush(stdout);

        exit(0);
    }
    else
    {
        printf("PARENT: Press <RETURN> to release the write lock\n\n");
        getchar();

        fl.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &fl);

        printf("PARENT: Unlocked the file\n");
        fflush(stdout);

        wait(NULL);
        close(fd);
    }
}