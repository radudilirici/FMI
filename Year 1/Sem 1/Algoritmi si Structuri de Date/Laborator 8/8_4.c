#include <stdio.h>
#include <stdlib.h>

void interclasare(int **v, int st, int mijl, int dr)
{
	int n = mijl - st;
	int m = dr - mijl;
	int S[n], D[m];
	int i, j;
	for (i = 0; i < n; i++)
		S[i] = (*v)[st+i];
	for (j = 0; j < m; j++)
		D[j] = (*v)[mijl+j];
	i = j = 0;
	int k = st;
	while (i < n && j < m)
	{
		if (S[i] < D[j])
			(*v)[k++] = S[i++];
		else
			(*v)[k++] = D[j++];
	}
	while (i < n)
		(*v)[k++] = S[i++];
	while (j < m)
		(*v)[k++] = D[j++];
}

void sortare_insertie(int **v, int st, int dr)
{
	int i, j;
	for (i = st; i < dr-1; i++)
	{
		int j=i;
		int x=(*v)[i+1];
		while (j>=st && x<(*v)[j])
		{
			(*v)[j+1]=(*v)[j];
			j--;
		}
		(*v)[j+1]=x;
	}
}

void MergeSort(int **v, int st, int dr)
{
	if (dr-st <= 1)
		return ;
	if (dr-st < 10)
	{
		sortare_insertie(v, st, dr);
		return;
	}

	int mijl = (st+dr) / 2;

	MergeSort(v, st, mijl);
	MergeSort(v, mijl, dr);

	interclasare(v, st, mijl, dr);
}

int main()
{
	int n, *A;
	scanf("%d", &n);
	A = (int*) malloc(n*sizeof(int));
	for (int i = 0; i < n; i++)
		scanf("%d", &A[i]);

	MergeSort(&A, 0, n);

	for (int i = 0; i < n; i++)
		printf("%d ", A[i]);
	printf("\n");

	free(A);
	return 0;
}
/*
22
432 435 546 543 3 32 7845 213678 45 653 8213 12738 213 455 976 43 486 826 874 461 84 34
*/