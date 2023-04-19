#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	//creating the pipe and checking for errors
	int pipefd[2];
	pid_t cpid;
	if(argc < 2) {
		exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	//forking the process
	cpid = fork;

	//redirecting input/outputs of processes
	dup2(pipefd[0], STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);

	//running the child process
	if (cpid == 0) {
		printf("Child process is running \n");
		// execlp(argv[2], argv[2], NULL);
		exit(0);
	}

	//running the parent process
	else if (cpid > 0) {
		int pid = cpid;
		int status = 0;
		waitpid(pid, &status, 0);
		printf("parent process running\n");
		// execlp(argv[1], argv[1], NULL);
		exit(0);
	}

	else {
		perror("fork");
	}


	return 0;
}
