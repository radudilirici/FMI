#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

pthread_mutex_t mtx;
sem_t sem;
const int mx = 10;
int crt = 0;

void barrier_point(){
	pthread_mutex_lock(&mtx);
	crt++;
	if (crt == mx){
		for (int i = 0; i < crt - 1; i++)
			sem_post(&sem);
		crt = 0;
		pthread_mutex_unlock(&mtx);
		return;
	}
	pthread_mutex_unlock(&mtx);
	sem_wait(&sem);
}

void *tfun(void *v){
	int tid = *(int*)v;
	printf("%d reached the barrier\n", tid);
	barrier_point();
	printf("%d passed the barrier\n", tid);
	return NULL;
}

int main()
{
	if (sem_init(&sem, 0, 0)){
		perror(NULL);
		return errno;
	}
	if (pthread_mutex_init(&mtx, NULL)){
		perror(NULL);
		return errno;
	}

	int nr_threads = mx;
	pthread_t *threads = calloc(nr_threads, sizeof(pthread_t));
	int *ids = malloc(nr_threads * sizeof(int));

	for (int i = 0; i < nr_threads; i++){
		ids[i] = i;
		if (pthread_create(&threads[i], NULL, tfun, &ids[i])){
			perror(NULL);
			return errno;
		}
	}

	for (int i = 0; i < nr_threads; i++){
		if (pthread_join(threads[i], NULL)){
			perror(NULL);
			return errno;
		}
	}

	pthread_mutex_destroy(&mtx);
	sem_destroy(&sem);
	free(threads);
	free(ids);
}