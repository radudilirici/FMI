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
	if (argc < 2){
		printf("lipseste numarul\n");
		return 1;
	}
	pid_t pid = fork();
	if (pid < 0)
		return errno;
	else if (pid == 0){
		printf("Parent PID = %d, Child PID = %d\n", getppid(), getpid());
		int x = atoi(argv[1]);
		printf("%d : %d ", x, x);
		while (x > 1){
			if (x % 2 == 0)
				x = x / 2;
			else
				x = 3 * x + 1;
			printf("%d ", x);
		}
		printf("\n");
	}
	else {
		wait(NULL);
	}
	return 0;
}
