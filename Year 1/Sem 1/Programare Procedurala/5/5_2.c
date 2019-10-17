
#include <stdio.h>

int cautare_binara(int v[], int st, int dr, int valcrt)
{
	if (st > dr)
		return -1;
	int mijl = (st+dr)/2;
	if (v[mijl] == valcrt)
		return mijl;
	if (v[mijl] > valcrt)
		return cautare_binara(v, st, mijl, valcrt);
	else
		return cautare_binara(v, mijl+1, dr, valcrt);
}

int main()
{
	int n, i, x, y;
	scanf("%d", &n);
	int v[n+1];
	for (i=1; i<=n; i++)
		scanf("%d", &v[i]);
	scanf("%d %d", &x, &y);
	x = cautare_binara(v, 1, n, x);
	y = cautare_binara(v, 1, n, y);
	if (x == -1 || y == -1)
		return 0;
	for (i=x+1; i<y; i++)
		printf("%d ", v[i]);
	return 0;
}