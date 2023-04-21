#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t cpid;
	if(argc < 2) {
		exit(EXIT_FAILURE);
	}
	//forking the process
	cpid = fork();

	if (cpid == 0) {
		int fd[2];
		if (pipe(fd) < 0) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid_t child = fork();
		if(child == 0) {
			if(dup2(fd[1], 1) < 0) {
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			printf("Process 1 Running\n");
			close(fd[0]);
			close(fd[1]);
			execlp(argv[1], argv[1], NULL);
		}
		else {
			int status = 0;
			waitpid(cpid, &status, 0);
			printf("Status: %d", status);

			if(dup2(fd[0], 0) < 0) {
				perror("dup2");
				exit(EXIT_FAILURE);
			}

			printf("Process 2 Running\n");
			// close(fd[0]);
			execlp(argv[2], argv[2], NULL);
		}
	}


	return 0;
}
