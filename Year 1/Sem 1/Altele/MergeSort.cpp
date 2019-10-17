#include <stdio.h>

void interclasare(int v[], int st, int mijl, int dr)
{
	int n=mijl-st;
	int m=dr-mijl;
	int S[n], D[m];
	int i, j;
	for (i=0; i<n; i++)
		S[i]=v[st+i];
	for (j=0; j<m; j++)
		D[j]=v[mijl+j];
	i=j=0;
	int k=st;
	while (i<n && j<m)
	{
		if (S[i]<D[j])
			v[k++]=S[i++];
		else
			v[k++]=D[j++];
	}
	while (i<n)
		v[k++]=S[i++];
	while (j<m)
		v[k++]=D[j++];
}

void MergeSort(int v[], int st, int dr)
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
	int A[]={6,5,4,3,2,1,0};
	int n;
	scanf("%d", &n);
	for (int i=0; i<n; i++)
		scanf("%d", &A[i]);
	MergeSort(A, 0, n);
	for (int i=0; i<n; i++)
      printf("%d ", A[i]);
	return 0;
}