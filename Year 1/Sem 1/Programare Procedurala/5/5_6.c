#include <stdio.h>
#include <stdlib.h>

int prim(int x)
{
    int i;
    for(i=2; i*i<=x; i++)
        if (x%i == 0)
            return i;
    return 0;
}

void fill(int v[100][100], int n)
{
    int i = 0, j = 0, k, ok = 1, valcrt = 1, divizor = 0;
    int st = 0, dr = n-1, sus = 0, jos = n-1;
    int x[] = {1, 0, -1, 0}, y[] = {0, 1, 0, -1};
    while (ok)
    {
        ok=0;
		for (k=0; k<4; k++)
		{
			while (i+y[k] >= sus && i+y[k] <= jos && j+x[k] >= st && j+x[k] <= dr)
			{
			    if (divizor)
                {
                    v[i][j] = divizor;
                    divizor = 0;
			    }
			    else
                {
                    v[i][j] = valcrt;
                    divizor = prim(valcrt);
                    valcrt++;
			    }
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
    if (divizor)
    {
        v[i][j] = divizor;
        divizor = 0;
    }
    else
    {
        v[i][j] = valcrt;
        divizor = prim(valcrt);
        valcrt++;
    }
}

int main()
{
    int n, v[100][100];
    scanf("%d", &n);
    fill(v, n);
    int i, j;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
            printf("%2d ", v[i][j]);
        printf("\n");
    }
    return 0;
}
