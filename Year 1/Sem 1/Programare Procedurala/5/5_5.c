#include <stdio.h>

int x[] = {1, 0, -1, 0}, y[] = {0, 1, 0, -1};

void citire(int v[100][100], int n, int m)
{
	int i, j;
	for (i=0; i<n; i++)
		for (j=0; j<m; j++)
			scanf("%d", &v[i][j]);
}

void afisare_spirala(int v[100][100], int n, int m)
{
	int ok = 1, i = 0, j = 0, k;
	int st = 0, dr = m-1, sus = 0, jos = n-1;
	while (ok)
	{
		ok=0;
		for (k=0; k<4; k++)
		{
			while (i+y[k] >= sus && i+y[k] <= jos && j+x[k] >= st && j+x[k] <= dr)
			{
				printf("%d ", v[i][j]);
				i += y[k];
				j += x[k];
				ok=1;
			}
			switch (k)
			{
				case 0: sus++; break;
				case 1: dr--; break;
				case 2: jos--; break;
				case 3: st++; break;
			}
		}
	}
	printf("%d\n", v[i][j]);
}

int main()
{
	int v[100][100];
	int n, m, i, j;
	scanf("%d %d", &n, &m);
	citire(v, n, m);
	afisare_spirala(v, n, m);
	return 0;
}