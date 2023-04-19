#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char child[] = argv[2];
	printf("argv[2]: %s\nchild: %s\n", argv[2], child);
	//creating the pipe and checking for errors
	int pipefd[2];
	pid_t cpid;
	char buf;
	if(argc != 2) {
		exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	//forking the process
	cpid = fork();

	//checking for errors in the fork
	if(cpid == fork()) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	printf(argv[2]);
	//switching child process to next argument
	if (cpid == 0) {
		execlp(child, child, NULL);
		printf("child process ran");
	}

	//running the parent process
	execlp(argv[1], argv[1], NULL);


	return 0;
}
