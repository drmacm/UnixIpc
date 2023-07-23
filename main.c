#include "common.h"
#include "fifos.c"
#include "forks.c"
#include "pipes1.c"
#include "pipes2.c"
#include "signals.c"

void usage()
{
    printf("Usage: ./unixipc <demo_name>\n");
    printf("Available demos:\n");
    printf("  forks\n");
    printf("  signals\n");
    printf("  pipes1\n");
    printf("  pipes2\n");
    printf("  fifos\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        usage();
        return 1;
    }

    if (strcmp(argv[1], "forks") == 0)
    {
        forks();
    }
    else if (strcmp(argv[1], "signals") == 0)
    {
        signals();
    }
    else if (strcmp(argv[1], "pipes1") == 0)
    {
        pipes1();
    }
    else if (strcmp(argv[1], "pipes2") == 0)
    {
        pipes2();
    }
    else if (strcmp(argv[1], "fifos") == 0)
    {
        fifos(argc, argv);
    }
    else
    {
        printf("Invalid argument: %s\n", argv[1]);
        usage();
        return 1;
    }

    return 0;
}
