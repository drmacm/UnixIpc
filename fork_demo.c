#include <stdlib.h>
#include <sys/types.h>

void fork_demo()
{
    int status_argument;
    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork");
        exit(1);
    case 0:
        printf("CHILD: PID: %d, parent's PID: %d\n", getpid(), getppid());
        exit(42);
    default:
        printf("PARENT: PID %d, chiddld's PID: %d\n", getpid(), pid);
        printf("PARENT: Waiting for child to exit()...\n");
        wait(&status_argument);
        // Low-order 8 bits of the status argument represent the exit code
        int exit_code = WEXITSTATUS(status_argument);
        printf("PARENT: Child's exit status: %d\n", exit_code);
        printf("PARENT: Full exit number: %d\n", status_argument);
    }
}
