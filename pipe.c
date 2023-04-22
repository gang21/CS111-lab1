#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	// //pipe creating
	// int fd[2];
	// if (pipe(fd) == -1) {
	// 	return(EXIT_FAILURE);
	// }
	// int cpid = fork();
	// if (cpid < 0) {
	// 	return(EXIT_FAILURE);
	// }
	// //child process
	// if(cpid == 0) {
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	execlp(argv[1], argv[1], NULL);

	// }
	// //parent
	// int ppid = fork();
	// if (ppid < 0) {
	// 	return(EXIT_FAILURE);
	// }
	// if(ppid == 0) {
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	execlp(argv[2], argv[2], NULL);
	// }
	// close(fd[0]);
	// close(fd[1]);
	// waitpid(cpid, NULL, 0);
	// waitpid(ppid, NULL, 0);


	////////////////////////////////////////////////
	/////////       for loop example      //////////
	////////////////////////////////////////////////

	int pipes[argc][2];
	int pids[argc - 1];
	int i;
	for (i = 0; i < argc; i++) {
		if (pipe(pipes[i]) == -1) {
			printf("Error with creating pipe\n");
			return(EXIT_FAILURE);
		}
	}

	for (i = 1; i < argc; i++) {
		//creating forks
		pids[i] = fork();
		if(pids[i] == -1) {
			printf("Error with creating processes\n");
			return(EXIT_FAILURE);
		}
		if(pids[i] == 0) {
			//child process
			int j;
			for(j = 0; j < argc; j++) {
				if(i != j) {
					close(pipes[j][0]);
				}
				if(i+1 != j) {
					close(pipes[j][1]);
				}
			}
			
			close(pipes[i][0]);
			close(pipes[i+1][1]);

			//if execlp doesn't work
			// return(EXIT_SUCCESS);
		}
		
		//main process
		if(i < argc - 1) {
			printf("This is loop #%d with p1: %s and p2: %s\n", i, argv[i], argv[i+1]);
		}		
	}

	for (i=0; i < argc - 1; i++) {
		wait(NULL);
	}

	return 0;
}
