#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int fd[2];
	if (pipe(fd) == -1) {
		return(EXIT_FAILURE);
	}
	int pid1 = fork();
	if (pid1 < 0) {
		return(EXIT_FAILURE);
	}
	//first process
	if(pid1 == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp(argv[1], argv[1], NULL);

	}

	int fd2[2];
	if(pipe(fd2) == -1) {
		return(EXIT_FAILURE);
	}

	//second process
	int pid2 = fork();
	if (pid2 < 0) {
		return(EXIT_FAILURE);
	}
	if(pid2 == 0) {
		dup2(fd[0], STDIN_FILENO);
		dup2(fd2[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(fd2[0]);
		close(fd2[1]);
		execlp(argv[2], argv[2], NULL);
	}

	waitpid(pid1, NULL, 0);
	close(fd[0]);
	close(fd[1]);
	close(fd2[0]);
	close(fd2[1]);

	int pid3 = fork();
	if(pid3 < 0) {
		return(EXIT_FAILURE);
	}
	if(pid3 == 0) {
		printf("PID3 WORKING\n");
		char buf[4096];
		read(fd2[0], buf, 20);
		printf("%s\n", buf);
		dup2(fd2[0], STDIN_FILENO);
		close(fd2[0]);
		close(fd2[1]);
		execlp(argv[3], argv[3], NULL);
	}

	close(fd2[0]);
	close(fd2[1]);
	waitpid(pid2, NULL, 0);
	waitpid(pid3, NULL, 0);

	return 0;
}
