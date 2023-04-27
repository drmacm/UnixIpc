#include <signal.h>
#include <stdio.h>

void sigint_handler(int sig)
{
    write(0, "\nI got interrupted!\n", 20);
}

void signals_demo()
{
    void sigint_handler(int sig);
    char s[200];
    struct sigaction sa = {
        .sa_handler = sigint_handler,
        .sa_flags = SA_RESTART,
    };
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }

    printf("Enter a string and press ENTER to exit.\n");
    printf("Press CTRL+C during typing to restart it.\n");

    if (fgets(s, sizeof s, stdin) == NULL)
        perror("fgets");
    else
        printf("You entered: %s\n", s);
}