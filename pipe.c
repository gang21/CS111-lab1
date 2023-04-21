#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t ppid;

	//checking if there are a valid number of args
	if(argc < 2) {
		exit(EXIT_FAILURE);
	}

	//forking the process
	ppid = fork();

	//parent (child of the shell)
	if (ppid == 0) {
		int fd[2];
		if (pipe(fd) < 0) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		//child
		pid_t cpid = fork();
		if(cpid == 0) {
			printf("Process 1 Running: %s\n", argv[1]);
			dup2(fd[1], 1);
			// 	printf("dup2\n");
			// 	exit(EXIT_FAILURE);
			// }
			close(fd[0]);
			close(fd[1]);
			execlp(argv[1], argv[1], NULL);
		}
		else {
			int status = 0;
			wait(0);
			printf("Status: %d\n", status);

			dup2(fd[0], 0);
			// 	perror("dup2");
			// 	exit(EXIT_FAILURE);
			// }

			printf("Process 2 Running: %s\n", argv[2]);
			close(fd[0]);
			execlp(argv[2], argv[2], NULL);
		}
	}


	return 0;
}
