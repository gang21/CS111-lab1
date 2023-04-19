#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	//checking for errors in the creation of the pipe/fork
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
	cpid = fork();
	if(cpid = fork()) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	execlp(argv[1], argv[1], NULL);



	return 0;
}
