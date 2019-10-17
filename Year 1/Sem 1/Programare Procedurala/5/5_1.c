#include <stdio.h>

int v[4001];

int main()
{
	int x, y, i, val;
	scanf("%d", &x);
	for (i=1; i<=x; i++)
	{
		scanf("%d", &val);
		v[val+2000]++;
	}
	scanf("%d", &y);
	for (i=1; i<=y; i++)
	{
		scanf("%d", &val);
		v[val+2000]++;
	}
	for (i=0; i<=4000; i++)
		if (v[i] >= 2)
			printf("%d ", i-2000);
	return 0;
}