#include <stdio.h>
#include <stdlib.h>

int **pseudo_matrice(int *n)
{
    FILE *f = fopen("siruri.txt", "r");

    if (f == NULL)
    {
        printf("Nu s-a putut deschide fisierul!\n");
        exit(1);
    }

    int **m = (int **) malloc(0);

    int ni, i, x, linii = 0;

    while (fscanf(f, "%d", &ni) == 1)
    {
        linii++;
        m = (int **) realloc(m, linii * sizeof(int *));
        if (m == NULL)
        {
            printf("NU MAI E MEMORIE!");
            exit(1);
        }
        m[linii - 1] = (int *) malloc((ni+1) * sizeof(int));
        m[linii - 1][0] = ni;
        for (i = 1; i <= ni; i++)
        {
            fscanf(f, "%d", &x);
            m[linii - 1][i] = x;
        }
    }

    fclose(f);

    *n = linii;
    return m;
}

void afisare(int **m, int n)
{
    printf("\n");
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 1; j <= m[i][0]; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}

int cmp(const void *a, const void *b)
{
    int va = *(int *) a;
    int vb = *(int *) b;

    return (va - vb);
}

int cmp_linii(const void *a, const void *b)
{
    int *va = *(int **) a;
    int *vb = *(int **) b;
    return (va[0] - vb[0]);
}

void sortare(int ***m, int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        qsort(&(*m)[i][1], (*m)[i][0], sizeof(int), cmp);
    }
    qsort(&(*m)[0], n, sizeof(int *), cmp_linii);
}

void interclasare(int **v, int **w)
{
    int i, j, k, n;
    i = 1;
    j = 1;
    n = (*v)[0] + (*w)[0];
    while (j <= (*w)[0])
    {
        if ((*v)[i] > (*w)[j] || i > (*v)[0])
        {
            (*v)[0]++;
            *v = realloc(*v, ((*v)[0]+1) * sizeof(int));
            for (k = (*v)[0]; k > i; k--)
                (*v)[k] = (*v)[k-1];
            (*v)[i] = (*w)[j];
            j++;
        }
        i++;
    }
    (*v)[0] = n;
    free(*w);
}

void interclasare_matrice(int ***m, int *n)
{
    int i;
    for (i = 1; i < *n; i++)
    {
        interclasare(&(*m)[0], &(*m)[i]);
    }
    *n = 1;
}

void scriere_vector(int *v)
{
    FILE *g = fopen("siruri.txt", "a");
    fseek(g, 0, SEEK_END);
    int i;
    fprintf(g, "\n\n");
    for (i = 1; i <= v[0]; i++)
        fprintf(g, "%d ", v[i]);
    fclose(g);
}

int main()
{
    int n;
    int **m = pseudo_matrice(&n);

    afisare(m, n);
    sortare(&m, n);
    interclasare_matrice(&m, &n);
    scriere_vector(m[0]);
    afisare(m, n);

    free(m);
/*
3
213 413 43
5
231 34 54 643 32
5
67 43 324 5 865
1
23
2
213 432
*/
    return 0;
}