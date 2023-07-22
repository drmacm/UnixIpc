#include "fork_demo.c"
#include "pipes_demo_1.c"
#include "pipes_demo_2.c"
#include "signals_demo.c"
#include <stdio.h>
#include <string.h>

void display_usage()
{
    printf("Usage: ./unixipc <demo_name>\n");
    printf("Available demos:\n");
    printf("  fork\n");
    printf("  signals\n");
    printf("  pipes1\n");
    printf("  pipes2\n");
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
    else if (strcmp(argv[1], "signals") == 0)
    {
        signals_demo();
    }
    else if (strcmp(argv[1], "pipes1") == 0)
    {
        pipes_demo_1();
    }
    else if (strcmp(argv[1], "pipes2") == 0)
    {
        pipes_demo_2();
    }
    else
    {
        printf("Invalid argument: %s\n", argv[1]);
        display_usage();
        return 1;
    }

    return 0;
}
