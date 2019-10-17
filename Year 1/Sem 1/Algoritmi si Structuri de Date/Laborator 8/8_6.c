#include <stdio.h>

int main()
{
    FILE *f = fopen("8_6.in", "r");
    FILE *g = fopen("8_6.out", "w");
    
    int n, i, j, varf, k, m, v[1000000], a[1000000];

    fscanf(f, "%d", &n);
    for (i = 0; i < n; i++)
        fscanf(f, "%d", &v[i]);

    i = 0;
    while (i < n)
    {
        j = i;
        while (v[i+1] >= v[i] && i < n - 1)
            i++;
        varf = i;
        while (v[i+1] <= v[i] && i < n - 1)
            i++;
        for (k = j; k <= i; k++)
            a[k] = varf;
        i++;
    }

    fscanf(f, "%d", &m);
    for (k = 0; k < m; k++)
    {
        fscanf(f, " %d %d", &i, &j);
        if (i == j)
        {
            fprintf(g, "%d", 1);
            continue;
        }

        while (v[i] == v[i - 1] && i < j)
            i++;

        if (a[i - 1] == a[j - 1] || a[i] == a[j - 1])
            fprintf(g, "%d", 1);
        else
            fprintf(g, "%d", 0);
    }
    fprintf(g, "\n");

    fclose(f);
    fclose(g);
    return 0;
}