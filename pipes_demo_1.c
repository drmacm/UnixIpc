#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void pipes_demo_1()
{
    int pfds[2];
    char s[200];

    pipe(pfds);

    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork");
        exit(1);
    case 0:
        close(pfds[0]); // Child can close reading end of the pipe
        printf("CHILD: Write a string to the pipe\n");
        fgets(s, sizeof(s), stdin);
        write(pfds[1], s, strlen(s) + 1);
        close(pfds[1]);
        printf("CHILD: exiting\n");
        exit(0);
    default:
        close(pfds[1]); // Parent can close writing end of the pipe
        printf("PARENT: reading from pipe\n");
        read(pfds[0], s, sizeof(s));
        printf("PARENT: Pipe contents: %s", s);
        close(pfds[0]);
        wait(NULL);
    }
}