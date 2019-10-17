#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

int partitionare(int v[], int st, int dr)
{
    int r = rand() % (dr - st + 1) + st;
    swap(&v[dr], &v[r]);
	int pivot=v[st];
	while (1)
	{
		while (v[st]<pivot)
			st++;
		while (v[dr]>pivot)
			dr--;
		if (st == dr)
			return st;
		swap(&v[st], &v[dr]);
	}
}

void QuickSort(int v[], int st, int dr)
{
	if (st>=dr)
		return;
	int pivot=partitionare(v, st, dr);
	QuickSort(v, st, pivot);
	QuickSort(v, pivot+1, dr);
}

int main()
{
	int n, v[101];
	scanf("%d", &n);
	for (int i=0; i<n; i++)
		scanf("%d", &v[i]);
	QuickSort(v, 0, n-1);
	for (int i=0; i<n; i++)
		printf("%d ", v[i]);
	return 0;
}
