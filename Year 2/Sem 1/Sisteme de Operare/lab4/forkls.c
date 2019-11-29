#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
	pid_t pid = fork();
	if (pid < 0)
		return errno;
	else if (pid == 0){
		printf("Parent PID = %d, Child PID = %d\n", getppid(), getpid());
		char *argv[] = {"ls", NULL};
		execve("/bin/ls", argv, NULL);
		perror(NULL);
	}
	else {
		wait(NULL);
	}
	return 0;
}
