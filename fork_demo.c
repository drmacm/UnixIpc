#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int fork_demo()
{
	pid_t pid;
	int child_exit_code;
	// Fork() creates a child process with the new PID and address space
	// Child process starts executing from here
	// Parent process will have child's PID in pid variable
	// Child process will have 0 in pid variable
	pid = fork();

	switch (pid)
	{
	case -1:
		perror("fork");
		exit(1);
	case 0:
		printf("CHILD: PID: %d, parent's PID: %d\n", getpid(), getppid());
		exit(6);
	default:
		printf("PARENT: PID %d, child's PID: %d\n", getpid(), pid);
		printf("PARENT: Waiting for child to exit()...\n");
		wait(&child_exit_code);
		// Low-order 8 bits of the status argument passed to exit()
		int exit_code = WEXITSTATUS(child_exit_code);
		printf("PARENT: Child's exit status: %d\n", exit_code);
	}

	return 0;
}
