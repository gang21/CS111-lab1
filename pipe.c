#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	printf("argc: %d", argc);
	for (int i = 0; i < argc; i++) {
		printf("argv[%d]: %s",i, argv[i]);
	}
	return 0;
}
