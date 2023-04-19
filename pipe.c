#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int return_code = fork();
  if (return_code == 0) {
    printf("This is the child process!\n");
    execlp("ls", "ls", NULL);
  } else if (return_code > 0) {
    printf("I am lazy parent, letting my child to ls the directory\n");
    printf("I will just wait for their report\n");
  } else {
    printf("Child process creation error! \n");
  }
  printf("They finished; Done!\n");
  return 0;
}
