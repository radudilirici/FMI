#include <stdio.h>

void interclasare(int v[], int st, int mijl, int dr)
{
	int n = mijl - st;
	int m = dr - mijl;
	int S[n], D[m];
	int i, j;
	for (i = 0; i < n; i++)
		S[i] = v[st+i];
	for (j = 0; j < m; j++)
		D[j] = v[mijl+j];
	i = j = 0;
	int k = st;
	while (i < n && j < m)
	{
		if (S[i]<D[j])
			v[k++] = S[i++];
		else
			v[k++] = D[j++];
	}
	while (i < n)
		v[k++] = S[i++];
	while (j < m)
		v[k++] = D[j++];
}

void insertion_sort(int v[], int st, int dr)
{
    int i, j, x;
    for (i = st + 1; i <= dr; i++)
    {
        j = i - 1;
        x = v[i];
        while (j >= st && x < v[j])
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = x;
    }
}

void MergeSort(int v[], int st, int dr)
{
	if (dr - st <= 1)
		return ;

    if (dr - st <= 11)
        insertion_sort(v, st, dr);
    else
    {
        int mijl = (st+dr)/2;

        MergeSort(v, st, mijl);
        MergeSort(v, mijl, dr);

        interclasare(v, st, mijl, dr);
    }
}



int main()
{
	int A[100];//={6,5,4,3,2,1,0};
	int n;
	scanf("%d", &n);
	for (int i=0; i<n; i++)
		scanf("%d", &A[i]);
	MergeSort(A, 0, n);
	for (int i=0; i<n; i++)
      printf("%d ", A[i]);
	return 0;
}
