#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv)
{
	if (argc != 3){
		printf("Wrong number of parameters(%d)\n", argc);
		return 1;
	}
	const char *fsrc = argv[1];
	const char *fdst = argv[2];
	int src = open(fsrc, O_RDONLY);
	int dst = open(fdst, O_WRONLY|O_CREAT, S_IRWXU);

	struct stat fileStat;

	if (stat(fsrc, &fileStat)){
		perror("eroare citire");
		return errno;
	}

	char buf[1024];
	size_t len = sizeof(buf);

	size_t nread = read(src, buf, len);
	if (nread < 0){
		printf("eroare citire\n");
		perror("read buf");
		return errno;
	}
	size_t nwrite = write(dst, buf, nread);
	if (nwrite < 0){
		printf("eroare scriere\n");
		perror("write buf");
		return errno;
	}
	return 0;
}
