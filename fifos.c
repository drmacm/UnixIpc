#define FIFO_PATH "myfifo"

void writer()
{
    char buffer[1024];
    int writefd;

    printf("Writer started, opening %s FIFO for writing\n", FIFO_PATH);
    writefd = open(FIFO_PATH, O_WRONLY);

    printf("Enter a message: ");
    fgets(buffer, sizeof(buffer), stdin);
    write(writefd, buffer, strlen(buffer) + 1);

    close(writefd);
    exit(0);
}

void reader()
{
    char buffer[1024];
    int readfd;

    printf("Reader started, opening %s FIFO for reading\n", FIFO_PATH);
    readfd = open(FIFO_PATH, O_RDONLY);
    read(readfd, buffer, sizeof(buffer));

    printf("Received message: %s\n", buffer);

    close(readfd);
    exit(0);
}

void fifos(int argc, char *argv[])
{
    if (argc == 2)
    {
        printf("Creating FIFO %s\n", FIFO_PATH);
        mknod(FIFO_PATH, S_IFIFO | S_IRUSR | S_IWUSR, 0);

        pid_t writer = fork();
        if (writer == 0)
        {
            printf("Writer process created, reexecuting the example with -w argument\n");
            execlp(argv[0], argv[0], argv[1], "-w", NULL);
        }

        pid_t reader = fork();
        if (reader == 0)
        {
            printf("Reader process created, reexecuting the example with -r argument\n");
            execlp(argv[0], argv[0], argv[1], "-r", NULL);
        }

        wait(NULL);
        wait(NULL);

        unlink(FIFO_PATH);
    }
    else if (argc == 3 && strcmp(argv[2], "-r") == 0)
    {
        reader();
    }
    else if (argc == 3 && strcmp(argv[2], "-w") == 0)
    {
        writer();
    }
}
