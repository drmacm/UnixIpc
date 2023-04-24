#include <stdio.h>
#include <string.h>
#include "fork_demo.c"

void display_usage()
{
    printf("Usage: ./unixipc <demo_name>\n");
    printf("Available demos:\n");
    printf("  fork\n");
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        display_usage();
        return 1;
    }

    if (strcmp(argv[1], "fork") == 0)
    {
        fork_demo();
    }
    else
    {
        printf("Invalid argument: %s\n", argv[1]);
        display_usage();
        return 1;
    }

    return 0;
}