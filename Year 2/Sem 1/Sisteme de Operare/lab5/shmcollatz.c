#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void collatz(int *buffer, int N){
	buffer[1] = N;
	int i = 2;
	while (N > 1){
		if (N % 2 == 0)
			N = N / 2;
		else
			N = 3 * N + 1;
		buffer[i] = N;
		i++;
	}
	buffer[0] = i - 1;
}

void print_collatz(int *buffer){
	printf("%d : ", buffer[1]);
	for (int i = 1; i <= buffer[0]; i++)
		printf("%d ", buffer[i]);
	printf("\n");
}


int main(int argc, char *argv[])
{
	char *shm_name = "/COLLATZ";
	int shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	if (shm_fd < 0){
		perror(NULL);
		return errno;
	}
	size_t shm_partition = 1024;
	size_t shm_size = shm_partition * (argc - 1);
	if (ftruncate(shm_fd, shm_size) == -1){
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}
	pid_t pid;
	for (int i = 1; i < argc; i++){
		pid = fork();
		if (pid < 0)
			return errno;
		else if (pid == 0){
			char *addr = mmap(0, shm_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
			char *buffer = addr + (i - 1) * shm_partition;
			int N = atoi(argv[i]);
			collatz((int*)buffer, N);
			printf("Done, Parent: %d Me: %d\n", getppid(), getpid());
			return 0;
		}
	}
	for (int i = 1; i < argc; i++){
		if (wait(NULL) == -1){
			perror("could not find child");
			return errno;
		}
	}
	char *addr = mmap(0, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);
	for (int i = 1; i < argc; i++)
		print_collatz((int*)(addr + (i-1) * shm_partition));
	if (munmap(addr, shm_size) != 0){
		shm_unlink(shm_name);
		perror("can't unmap memory");
		return errno;
	}
	shm_unlink(shm_name);
	return 0;
}
