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

	if (stat(fsrc, &fileStat) != 0){
		printf("Fisier deja existent\n");
		return 1;
	}

	char buf[1024];
	size_t len = sizeof(buf);

	while (1){
		size_t nread = read(src, buf, len);
		if (nread == 0){
			break;
		}
		if (nread < 0){
			close(src);
			close(dst);
			printf("eroare citire\n");
			perror("read buf");
			return errno;
		}
		size_t twrite = 0;
		while (1){
			size_t nwrite = write(dst, &(buf[twrite]), nread);
			if (nwrite < 0){
				printf("eroare scriere\n");
				perror("write buf");
				return errno;
			}
			twrite += nwrite;
			if (twrite == nread){
				break;
			}
		}
	}
	close(src);
	close(dst);
	return 0;
}
