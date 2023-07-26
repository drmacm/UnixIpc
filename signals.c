#include "common.h"

void sigint_handler(int sig)
{
    write(0, "\nI got interrupted!\n", 20);
}

void signals()
{
    void sigint_handler(int sig);
    char s[200];
    struct sigaction sa = {
        .sa_handler = sigint_handler,
        .sa_flags = SA_RESTART,
    };
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);

    printf("Enter a string and press ENTER to exit.\n");
    printf("Press CTRL+C during typing to restart it.\n");

    fgets(s, sizeof s, stdin);
    printf("You entered: %s\n", s);
}