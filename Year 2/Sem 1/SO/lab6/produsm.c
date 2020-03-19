#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>

int A[4][5], B[5][6], C[4][6];

void *prod(void *v){
	int *idx = (int*)v;
	int a = idx[0];
	int b = idx[1];
	int rez = 0;
	for (int i = 0; i < 5; i++){
		rez += A[a][i] * B[i][b];
	}
	C[a][b] = rez;
	return NULL;
}

int main(int argc, char*argv[])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 5; j++){
			A[i][j] = rand() % 10;
		}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 6; j++)
			B[i][j] = rand() % 10;

	pthread_t thr[4 * 6];

	int b = 0;
	for (int a = 0; a < 4;){
		int nr_crt = a * 6 + b;
		int idx[] = {a, b};
		void *v = (void*)idx;
		if (pthread_create(&thr[nr_crt], NULL, prod, idx)){
			perror(NULL);
			return errno;
		}
		if (pthread_join(thr[nr_crt], NULL)){
			perror(NULL);
			return errno;
		}
		if (b < 6)
			b++;
		else{
			b = 0;
			a++;
		}
	}

	//for (int i = 0; i < 4 * 6; i++)
	//	if (pthread_join(thr[i], NULL)){
	//		perror(NULL);
	//		return errno;
	//	}

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 6; j++)
			printf("%d ", C[i][j]);
		printf("\n");
	}
	return 0;
}
