#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>

void *rev(void *v);

int main(int argc, char *argv[])
{
	pthread_t thr;
	if (pthread_create(&thr, NULL, rev, argv[1])){
		perror(NULL);
		return errno;
	}
	void *reversed;
	if (pthread_join(thr, &reversed)){
		perror(NULL);
		return errno;
	}
	char *result = (char*)reversed;
	printf("%s\n", result);
	return 0;
}

void *
rev(void *v){
	char *str = (char *)v;
	int n = strlen(str);
	char *aux = (char *) malloc(n + 1);
	for(int i = 0; i < n; i++)
		aux[n - i - 1] = str[i];
	aux[n] = '\0';
	return (void*)aux;
}
