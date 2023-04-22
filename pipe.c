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

	int PROCESS_NUM = argc - 1;
	int pipes[PROCESS_NUM + 1][2];
	int pids[PROCESS_NUM];
	int i;

	//creating all the pipes
	for(i = 0; i < PROCESS_NUM + 1; i++) {
		if(pipe(pipes[i]) == -1) {
			printf("error with creating pipe\n");
			exit(EXIT_FAILURE);
		}
	}

	//first process
	int j;
	for(j = 0; j < PROCESS_NUM + 1; j++) {
		if (j != PROCESS_NUM) {
			close(pipes[j][0]);
		}
		if(j != 0) {
			close(pipes[j][1]);
		}
	}
	pids[0] = fork();
	if (pids[0] == 0) {
		printf("First Process: %s\n", argv[1]);
		dup2(pipes[1][1], STDOUT_FILENO);
		execlp(argv[1], argv[1], NULL);
	}

	waitpid(pids[0], 0, 0);

	//creating actual processes
	for(i = 1; i < PROCESS_NUM-1; i++) {
		pids[i] = fork();
		if(pids[i] == -1) {
			printf("Error with creating processes\n");
			exit(EXIT_FAILURE);
		}
		//child process
		if (pids[i] == 0) {
			//closing unused pipes
			int j;
			for(j = 0; j < PROCESS_NUM + 1; j++) {
				if (i != j) {
					close(pipes[j][0]);
				}
				if(i+1 != j) {
					close(pipes[j][1]);
				}
			}

			int cpid = fork();
			if(cpid == 0) {
				dup2(pipes[i], STDIN_FILENO);
				dup2(pipes[i+1],STDOUT_FILENO);
				execlp(argv[i+1], argv[i+1], NULL);
			}
			int status = 0;
			// waitpid(cpid, &status, 0);
			if(status != 0) {
				printf("error with process %s\n", argv[i]);
				exit(EXIT_FAILURE);
			}
			printf("(%d) Got %s\n", i,argv[i+1]);

			// int x;
			// if(read(pipes[i][0], &x, sizeof(int)) == -1) {
			// 	printf("Error at reading\n");
			// 	exit(EXIT_FAILURE);
			// }

			// x++;
			// if(write(pipes[i+1][1], &x, sizeof(int)) == -1) {
			// 	printf("Error at writing\n");
			// 	exit(EXIT_FAILURE);
			// }
			// printf("(%d) Sent %s\n", i,argv[i]);

			close(pipes[i][0]);
			close(pipes[i+1][1]);
			return 0;
		}
	}

	//wait for all child processes to finish execution
	for(i = 0; i < PROCESS_NUM; i++) {
		wait(NULL);
	}

	for(j = 0; j < PROCESS_NUM + 1; j++) {
		if (j != PROCESS_NUM) {
			close(pipes[j][0]);
		}
		if(j != 0) {
			close(pipes[j][1]);
		}
	}

	//last process
	pids[PROCESS_NUM] = fork();
	if (pids[PROCESS_NUM] == 0) {
		printf("Last Process: %s\n", argv[PROCESS_NUM]);
		dup2(pipes[PROCESS_NUM-1][0], STDIN_FILENO);
		execlp(argv[PROCESS_NUM], argv[PROCESS_NUM], NULL);
	}

	waitpid(pids[PROCESS_NUM], 0, 0);

	//closing first input and last output pipes
	close(pipes[0][1]);
	close(pipes[PROCESS_NUM][0]);

	return 0;
}
