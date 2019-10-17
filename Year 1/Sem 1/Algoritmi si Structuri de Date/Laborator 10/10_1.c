#include <stdio.h>
#include <stdlib.h>

int grad(int x, int n, int m[100][100])
{
    int i, nr = 0;
    for (i =0; i < n; i++)
        if (m[x-1][i] == 1)
            nr++;
    return nr;
}

int muchii(int n, int m[100][100])
{
    int i, nr = 0;
    for (i = 0; i < n; i++)
        nr += grad(i, n, m);

    return nr/2;
}

void GradMax(int n, int m[100][100])
{
    int i, mxcrt, mx = -1;
    for (i = 0; i < n; i++)
    {
        mxcrt = grad(i, n, m);
        if (mxcrt > mx)
            mx = mxcrt;
    }
    for (i = 0; i < n; i++)
        if (grad(i, n, m) == mx)
            printf("%d ", i);
    printf("\n");
}

int main()
{
    FILE *f = fopen("data.in", "r");

    int n, i, j;
    int m[100][100];

    fscanf(f, "%d", &n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            fscanf(f, " %d", &m[i][j]);

    fclose(f);

    printf("%d\n", grad(2, n, m));
    printf("%d\n", muchii(n, m));
    GradMax(n, m);

    return 0;
}
