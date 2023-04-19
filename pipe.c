#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char *args[] = {"ls", "-aF", "/", NULL};
	char *env[] = {NULL};
	printf("About to run execve\n");
	execve("/bin/ls", args, env);

	perror("execve");
	exit(1);
}
