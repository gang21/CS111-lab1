#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int rc = fork();
	if (rc == 0) {
		printf("child process\n");
	}
	else if (rc > 0){
		printf("parent process\n");
	}
	else {
		printf("fork error\n");
	}
}
