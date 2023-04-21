#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	//pipe creating
	int fd[2];
	if (pipe(fd) == -1) {
		return(EXIT_FAILURE);
	}
	int cpid = fork();
	if (cpid < 0) {
		return(EXIT_FAILURE);
	}
	//child process
	if(cpid == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp(argv[1], argv[1], NULL);

	}
	//parent
	int ppid = fork();
	if (ppid < 0) {
		return(EXIT_FAILURE);
	}
	if(ppid == 0) {
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp(argv[2], argv[2], NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(cpid, NULL, 0);
	waitpid(ppid, NULL, 0);

	return 0;
}
