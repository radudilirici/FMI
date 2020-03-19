/*
	Author: Alex Mircescu	7 Nov 2019

	Description:
		Example of the pthread library, that multiplies a matrix
		in parallel threads, for each item of the resulting matrix
		using one thread to compute the result.

		This example will use the new functions, called:
			- pthread_create
			- pthread_join

		.. and also will exemplify creating our own type definition
			- matrix_t

*/

#include <pthread.h>// for pthread_x functions
#include <errno.h>  // for errno
#include <stdio.h>  // for printf
#include <string.h> // for strlen
#include <stdlib.h> // for EXIT_FAILURE, EXIT_SUCCESS constantts

/* 
	a type definition from a C-type struct, describing
	matrix data and information
*/
typedef struct struct_matrix{

	int ** matrix;
	int rows, cols;
} * matrix_t;

/*
	stucture describing the input data required for a thread
	to compute matrix multiplication for one item
*/
struct thread_job {
	matrix_t m1,m2;
	matrix_t result;
	int row, col;
};

/* 
	allocate matrix to a single block of memory

	Note: this allows us to create very large matrixes,
		  avoids memory fragmentation and provides a
		  continous space for matrix items, which gives us
		  the ability to use any type of memory to store them

		  (e.g. shared memory, but we have to change the allocation
		   function)
*/
matrix_t matrix_alloc(int rows, int cols) {

	size_t size =
                sizeof(struct struct_matrix) +  // space for structure
                rows * cols * sizeof(int) +     // space for matrix items
                rows * sizeof(int*);            // space for row points

	// allocate single block of memory
	matrix_t m = malloc(size);

	// OOM
	if (m==NULL) return NULL;

	// create a 'buffer' pointer to help us move around
	// in our block of memory; it starts with the first 
	// byte after structure
	char * buffer = (char*)m + sizeof(struct struct_matrix);

	// init struct
	// note: when m->matrix[0] will be called
	//	it will actually use the first sizeof(int*) 
	//	bytes from current address of buffer,
	//	to store the address of matrix data,
	//	cooresponding to that row
	m->matrix = (int**) buffer;
	m->rows = rows;
	m->cols = cols;

	// move buffer pointer after the set of pointers
	// describing rows data
	buffer += rows * sizeof(int*);

	// init each 'row' pointer with the correct
	// buffer pointing towards column items
	int ** row = &m->matrix[0]; 	// ecquivalent to row == m->matrix
					// just more readable

	// for each row, initialize the address that matches with
	// its row data and increment 'buffer' accordingly
	while(rows--) {
		* row = (int*) buffer;
		++ row;
		buffer += sizeof(int) * cols;
	}

	// done
	return m;
}

/* free memory allocated for this matrix */
void matrix_free(matrix_t m) {
	free(m); // matrix is actually just a single block of memory
}

/* randomize matrix data */
void matrix_rand(matrix_t m, int modulo) {
	int ** matrix = m->matrix;

	for (int i=0; i < m->rows; ++ i)
		for(int j=0; j < m->cols; ++j) {
			matrix[i][j] = rand() % modulo;
		}
}

/* print matrix to stdout */
void matrix_print(matrix_t m,const char*name){
        int ** matrix = m->matrix;

	printf("%s -> %d x %d matrix:\n",
		name, m->rows, m->cols);

        for (int i=0; i < m->rows; ++ i) {
                for(int j=0; j < m->cols; ++j)
                        printf("[%.3d]", matrix[i][j]);

		printf("\n");
	}
}

/* 
	getter functions
	note: it allows us to hide the internals of the matrix structure
		from the users using it
*/
int matrix_rows(matrix_t m) {
	return m->rows;
}

int matrix_cols(matrix_t m) {
	return m->cols;
}

int ** matrix_data(matrix_t m){
	return m->matrix;
}

/* thread that calculates one item from the result matrix */
void * thread_multiply (void * arg) {

	struct thread_job * tj = arg;

	// fetch data
	// p   - common matrix dimension
	// i,j - target row/column coordinates
	// res - target matrix
	// m1  - first matrix
	// m2  - second matrix
	int p   = matrix_cols(tj->m1);
	int i   = tj->row;
	int j   = tj->col;;
	int ** res = matrix_data(tj->result);
	int ** m1  = matrix_data(tj->m1);
	int ** m2  = matrix_data(tj->m2);

	// compute
	res[i][j] = 0;
	for (int k=0; k<p; ++k)
		res[i][j] = m1[i][k] * m2[k][j];

	return tj; // done
}

/* main function */
int main(int argc, char * argv[]) {

	// check arguments, print usage
	if (argc != 4) {
		printf("Usage: %s M N P\n", argv[0]);
		return EXIT_FAILURE;
	}

	// change this for different matrix sizes
	int m = atoi(argv[1]), n = atoi(argv[2]), p=atoi(argv[3]);
	int exit_code = EXIT_SUCCESS;

	// validate input
	if (m <= 0 || n <= 0 || p <= 0) {
		puts("invalid arguments");
		return EXIT_FAILURE;
	}

	// allocate input matrix
	matrix_t m1 = matrix_alloc(m,p);
	matrix_t m2 = matrix_alloc(p,n);
	matrix_t res = matrix_alloc(m,n);

	if (m1 == NULL || m2 == NULL || res == NULL ){
		puts("out of memory");
		exit_code = EXIT_FAILURE;
		goto cleanup;
	}

	// make all random
	matrix_rand(m1,100);
	matrix_rand(m2,100);
	matrix_rand(res,100);

	// print input matrixes
	matrix_print(m1,"m1");
	matrix_print(m2,"m2");

	int cnt_threads = m * n;

	// allocate thread arguments, initialize w/ 0
	struct thread_job * jobs = calloc(
		cnt_threads, sizeof(struct thread_job));

	// prepare pthreads, initialize w/ 0
	pthread_t * threads = calloc(
		cnt_threads, sizeof(pthread_t));

	if (jobs == NULL || threads == NULL ) {
		puts("out of memory");
		exit_code = EXIT_FAILURE;
		goto cleanup;
	}

	// prepare each job
	printf("------ \nCreating %d threads\n", cnt_threads);
	for (int i=0; i<cnt_threads; ++i) {

		struct thread_job * tj = &jobs[i];
		
		// prepare job data
		tj->m1 = m1;
		tj->m2 = m2;
		tj->result = res;
		tj->row = i / n;
		tj->col = i % n;

		// start thread
		pthread_t thread;
		exit_code = pthread_create(
			&thread, NULL, thread_multiply, tj);

		// failed to start, wait for previous threads, exit
		if (exit_code != 0) {
			errno = exit_code; perror("creating thread");
			while(--i) { pthread_join(threads[i],NULL); }
			goto cleanup;
		}

		// store thread handler
		threads[i] = thread;
	}

	// join all threads
	puts("Waiting for threads to finish ..");
	for (int i=0; i < cnt_threads; ++i)
		pthread_join(threads[i],NULL);

	// now print result
	puts("Done!\n------");
	matrix_print(res,"result");

	cleanup:

	if (exit_code != 0)
		printf("Execution failed: %d\n",exit_code);

	if (m1 != NULL ) matrix_free(m1);
	if (m2 != NULL ) matrix_free(m2);
	if (res != NULL ) matrix_free(res);
	if (jobs != NULL ) free(jobs);
	if (threads != NULL ) free(threads);

	return exit_code;
}