#include "common.h"

void pipes2()
{
    int pfds[2];

    pipe(pfds);

    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork");
        exit(1);
    case 0:
        printf("CHILD: Piping 'ls' output to parent\n");
        close(pfds[0]); // Child can close reading end of the pipe
        close(1);       // Close stdout to make it available for dup() system call
        dup(pfds[1]);   // Duplicate writing end to first available file descriptor
        execlp("ls", "ls", NULL);
        close(pfds[1]);
        exit(0);
    default:
        printf("PARENT: Counting lines in 'ls' output with 'wc -l' command\n");
        close(pfds[1]); // Parent can close writing end of the pipe
        close(0);       // Close stdin to make it available for dup() system call
        dup(pfds[0]);   // Duplicate reading end to first available file descriptor
        execlp("wc", "wc", "-l", NULL);
        close(pfds[0]);
        wait(NULL);
    }
}