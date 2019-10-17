#include <stdio.h>
#include <stdlib.h>

void interclasare_biton(int **v, int st, int varf, int dr, int tip)
{
	// daca tip = 1 inseamna ca varful e maximul, daca e -1, e minimul
	int n = varf - st;
	int m = dr - varf;
	int S[n], D[m];
	int i, j;
	for (i = 0; i < n; i++)
		S[i] = (*v)[st+i];
	for (j = 0; j < m; j++)
		D[j] = (*v)[dr-j-1];
	i = j = 0;
	int k = st;
	while (i < n && j < m)
	{
		if ((S[i] - D[j]) * tip <= -1)
			(*v)[k++] = S[i++];
		else
			(*v)[k++] = D[j++];
	}
	while (i < n)
		(*v)[k++] = S[i++];
	while (j < m)
		(*v)[k++] = D[j++];
}

int main()
{
	int *A, i, n, tip = 1;
	scanf("%d", &n);
	A = (int*) malloc(n*sizeof(int));
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);

	if (A[0] > A[1])
		tip = -1;

	int varf = n-1;
	for (i = 0; i < n-1; i++)
		if ((A[i] - A[i+1]) * tip >= 1)
		{
			varf = i;
			break;
		}

	interclasare_biton(&A, 0, varf, n, tip);

	if (tip = -1)
	{
		int *aux;
		aux = (int*) malloc(n*sizeof(int));
		for (i = 0; i < n; i++)
			aux[i] = A[n-i-1];
		for (i = 0; i < n; i++)
			A[i] = aux[i];
	}

	for (i = 0; i < n; i++)
		printf("%d ", A[i]);
	printf("\n");
	free(A);
	return 0;
}
/*
13
5 6 43 75 200 213 45 34 32 12 7 3 2
9
3242 434 325 213 54 321 542 2135 5677
*/