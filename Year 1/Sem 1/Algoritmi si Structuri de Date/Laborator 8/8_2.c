#include <stdio.h>
#include <stdlib.h>

void interclasare(int **v, int st, int mijl, int dr)
{
	int n=mijl-st;
	int m=dr-mijl;
	int S[n], D[m];
	int i, j;
	for (i=0; i<n; i++)
		S[i]=(*v)[st+i];
	for (j=0; j<m; j++)
		D[j]=(*v)[mijl+j];
	i=j=0;
	int k=st;
	while (i<n && j<m)
	{
		if (S[i]<D[j])
			(*v)[k++]=S[i++];
		else
			(*v)[k++]=D[j++];
	}
	while (i<n)
		(*v)[k++]=S[i++];
	while (j<m)
		(*v)[k++]=D[j++];
}

void MergeSort(int **v, int st, int dr)
{
	if (dr-st<=1)
		return ;

	int mijl=(st+dr)/2;

	MergeSort(v, st, mijl);
	MergeSort(v, mijl, dr);

	interclasare(v, st, mijl, dr);
}

int main()
{
	int n, *A;
	scanf("%d", &n);
	A = (int*) malloc(n*sizeof(int));
	for (int i=0; i<n; i++)
		scanf("%d", &A[i]);

	MergeSort(&A, 0, n);

	for (int i=0; i<n; i++)
		printf("%d ", A[i]);
	printf("\n");

    free(A);
	return 0;
}
