#include <stdio.h>

int A[100][100], B[100][100];
int main()
{
	int n, m, i, j;
	scanf("%d %d", &n, &m);
	for (i=0; i<n; i++)
		for (j=0; j<m; j++)
			scanf("%d", &A[i][j]);
	for (j=0; j<m; j++)
		for (i=0; i<n; i++)
			B[j][i] = A[i][j];
	for (j=0; j<m; j++)
	{
		for (i=0; i<n; i++)
			printf("%d ", B[j][i]);
		printf("\n");
	}
	return 0;
}