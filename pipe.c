#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// pid_t ppid;

	// //checking if there are a valid number of args
	// if(argc < 2) {
	// 	exit(EXIT_FAILURE);
	// }

	// //forking the process
	// ppid = fork();

	// //parent (child of the shell)
	// if (ppid == 0) {
	// 	int fd[2];
	// 	if (pipe(fd) < 0) {
	// 		perror("pipe");
	// 		exit(EXIT_FAILURE);
	// 	}

	// 	//child
	// 	pid_t cpid = fork();
	// 	if(cpid == 0) {
	// 		printf("Process 1 Running: %s\n", argv[1]);
	// 		dup2(fd[1], STDOUT_FILENO);
	// 		// 	printf("dup2\n");
	// 		// 	exit(EXIT_FAILURE);
	// 		// }
	// 		close(fd[0]);
	// 		close(fd[1]);
	// 		execlp(argv[1], argv[1], NULL);
	// 	}
		
	// 		int status = 0;
	// 		waitpid(cpid, &status, 0);
	// 		printf("Child process exits with code: %d\n", status);

	// 		dup2(fd[0], STDIN_FILENO);
	// 		// 	perror("dup2");
	// 		// 	exit(EXIT_FAILURE);
	// 		// }

	// 		printf("Process 2 Running: %s\n", argv[2]);
	// 		char buffer[4096];
	// 		read(fd[0], buffer, 20);
	// 		printf("%s\n", buffer);
	// 		close(fd[0]);
	// 		// execlp(argv[2], argv[2], NULL);
		
	// }

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
	waitpid(cpid, NULL, 0);
	waitpid(ppid, NULL, 0);




	return 0;
}
