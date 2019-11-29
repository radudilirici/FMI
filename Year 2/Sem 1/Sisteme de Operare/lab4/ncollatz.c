#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv)
{
	pid_t pid;
	for (int i = 1; i < argc; i++){
		pid = fork();
		if (pid < 0)
			return errno;
		else if (pid == 0){
			printf("Parent PID = %d, Child PID = %d\n", getppid(), getpid());
			int x = atoi(argv[i]);
			printf("%d : %d ", x, x);
			while (x > 1){
				if (x % 2 == 0)
					x = x / 2;
				else
					x = 3 * x + 1;
				printf("%d ", x);
			}
			printf("\n");
			return 0;
		}
	}
	for (int i = 1; i < argc; i++){
		wait(NULL);
		printf("Done\n");
	}
	return 0;
}
