#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	fork();
	printf("HI\n");
	return 0;
}
