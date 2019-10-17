#include <stdio.h>

int maxim(int v[], int n)
{
	int m=v[0];
		for (int i=1; i<n; i++)
			if (v[i]>m)
				m=v[i];
	return m;
}

void countSort(int v[], int n, int exp)
{
	int arr[n], i;
	int count[10]={0};
	for (i=0; i<n; i++)
		count[v[i]/exp%10]++;
	for (i=1; i<n; i++)
		count[i]+=count[i-1];
	for (i=n-1; i>=0; i--)
	{
		arr[count[v[i]/exp%10]-1]=v[i];
		count[v[i]/exp%10]--;
	}
	for (i=0; i<n; i++)
		v[i]=arr[i];
}

void RadixSort(int v[], int n)
{
	int m=maxim(v, n);
	int p=1;
	for (int i=1; i<=m; i*=10)
		countSort(v, n, i);
}

void in(int v[], int n)
{
	for (int i=0; i<n; i++)
		scanf("%d", &v[i]);
}

void out(int v[], int n)
{
	for (int i=0; i<n; i++)
		printf("%d ", v[i]);
	printf("\n");
}

int main()
{
	int n, v[101];
	scanf("%d", &n);
	in(v, n);
	RadixSort(v, n);
	out(v, n);
	return 0;
}