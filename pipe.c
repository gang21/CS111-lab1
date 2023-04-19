#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd = open("my_new_file.txt", O_APPEND|O_WRONLY);
	if (fd < 0)
		printf("Error opening the file\n");
	dup2(fd, STDOUT_FILENO);
	printf("print to the my_new_file.txt, instead of the console \n");
	return 0;
}
