#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_RESOURCES 5

int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx;

int decrease_count(int count){

	pthread_mutex_lock(&mtx);
	if (available_resources < count){
		pthread_mutex_unlock(&mtx);
		return -1;
	}
	available_resources -= count;
	printf("Got %d resources, remaining: %d\n", count, available_resources);
	pthread_mutex_unlock(&mtx);
	for (int i = 0 ; i < 100000; i++);
	return 0;
}

int increase_count(int count){
	pthread_mutex_lock(&mtx);
	available_resources += count;
	printf("Returned %d resources\n", count);
	pthread_mutex_unlock(&mtx);
	return 0;
}

void* use_resources(void* vcount){
	int count = *(int*)vcount;
	if (decrease_count(count) == -1){
		return NULL;
	}
	increase_count(count);
	return NULL;
}

int main()
{
	if (pthread_mutex_init(&mtx, NULL)){
		perror(NULL);
		return errno;
	}

	int nr_threads = 10;
	pthread_t *threads = calloc(nr_threads, sizeof(pthread_t));
	int *counts = malloc(nr_threads * sizeof(int));

	for (int i = 0; i < nr_threads; i++){
		counts[i] = rand() % 5 + 1;
		if (pthread_create(&threads[i], NULL, use_resources, &counts[i])){
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
	free(threads);
	free(counts);

	return 0;
}
