#include <stdio.h>
#include <stdlib.h>

int **triunghi(int n)
{
    int i, j;
    int **t = (int **) malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        t[i] = (int *) malloc((i + 1) * sizeof(int));

    for (i = 0; i < n; i++)
        for (j = 0; j <=i; j++)
            t[i][j] = 0;

    for (i = 0; i < n; i++)
        t[n - 1][i] = t[n - i - 1][0] = i + 1;

    for (i = n - 2; i >= 0; i--)
        for (j = 1; j <= i; j++)
            t[i][j] = t[i + 1][j] + t[i][j - 1];

    return t;
}
int main()
{
    int n;
    int i, j;
    scanf("%d", &n);
    int **t = triunghi(n);

    printf("\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j <=i; j++)
            printf("%d ", t[i][j]);
        printf("\n");
    }
    return 0;
}
