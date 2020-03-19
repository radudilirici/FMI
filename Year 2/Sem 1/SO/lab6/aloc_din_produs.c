#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct struct_matrix{
	int **matrix;
	int rows, cols;
} matrix_t;

typedef struct struct_thread{
	matrix_t *m1, *m2;
	matrix_t *result;
	int row, col;
} thread_job_t;

matrix_t *matrix_alloc(int rows, int cols){

	matrix_t *m = malloc(sizeof(matrix_t));

	if (m == NULL)
		return NULL;

	m->matrix = malloc(rows * sizeof(int*));

	if (m->matrix == NULL)
		return NULL;

	for (int i = 0; i < rows; i++){
		m->matrix[i] = malloc(cols * sizeof(int));
		if (m->matrix[i] == NULL)
			return NULL;
	}
	m->rows = rows;
	m->cols = cols;

	return m;
}

void matrix_rand(matrix_t *m, int modulo) {

	for (int i = 0; i < m->rows; i++)
		for(int j = 0; j < m->cols; j++)
			m->matrix[i][j] = rand() % modulo;
}

void matrix_print(matrix_t *m, const char *name){

	printf("%s -> %d x %d matrix:\n", name, m->rows, m->cols);

	for (int i = 0; i < m->rows; i++) {
		for(int j = 0; j < m->cols; j++)
			printf(" %.2d ", m->matrix[i][j]);
		printf("\n");
	}
}

void *thread_multiply(void *arg){

	thread_job_t *tj = (thread_job_t*) arg;

	int p = tj->m1->cols;
	int row = tj->row;
	int col = tj->col;;
	int ** result = tj->result->matrix;
	int ** m1  = tj->m1->matrix;
	int ** m2  = tj->m2->matrix;

	result[row][col] = 0;
	for (int i = 0; i < p; i++)
		result[row][col] += m1[row][i] * m2[i][col];

	return NULL;
}

int main(int argc, char *argv[]){

	if (argc != 4){
		puts("Wrong number of arguments");
		exit(1);
	}

	int m = atoi(argv[1]), p = atoi(argv[2]), n = atoi(argv[3]);

	matrix_t *A = matrix_alloc(m, p);
	matrix_t *B = matrix_alloc(p, n);
	matrix_t *C = matrix_alloc(m, n);

	if (A == NULL || B == NULL || C == NULL){
		puts("Out of memory");
		goto cleanup;
	}

	matrix_rand(A, 10);
	matrix_rand(B, 10);

	matrix_print(A, "A");
	matrix_print(B, "B");

	int nr_threads = n * m;

	thread_job_t *thread_jobs = calloc(nr_threads, sizeof(thread_job_t));
	pthread_t *threads = calloc(nr_threads, sizeof(pthread_t));

	if (thread_jobs == NULL || threads == NULL){
		puts("Out of memory");
		goto cleanup;
	}

	printf("\nCreating %d threads\n", nr_threads);

	for (int i = 0; i < nr_threads; i++)
	{
		thread_jobs[i].m1 = A;
		thread_jobs[i].m2 = B;
		thread_jobs[i].result = C;
		thread_jobs[i].row = i / n;
		thread_jobs[i].col = i % n;

		if (pthread_create(&threads[i], NULL, thread_multiply, &thread_jobs[i])){
			perror(NULL);
			goto cleanup;
		}
	}

	puts("Waiting for threads to finish\n");

	for (int i = 0; i < nr_threads; i++)
		if (pthread_join(threads[i], NULL)){
			perror(NULL);
			goto cleanup;
		}

	puts("Done\n");

	matrix_print(C, "C");

	cleanup:
	if (A != NULL ){
		for (int i = 0; i < m; i++)
			free(A->matrix[i]);
		free(A);
	}
	if (B != NULL ){
		for (int i = 0; i < p; i++)
			free(B->matrix[i]);
		free(B);
	}
	if (C != NULL ){
		for (int i = 0; i < m; i++)
			free(C->matrix[i]);
		free(C);
	}
	if (thread_jobs != NULL )
		free(thread_jobs);
	if (threads != NULL )
		free(threads);	

	return 0;
}