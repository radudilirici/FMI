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
    int pivot = v[dr];
    int i = st-1;
    for (int j = st; j < dr; j++)
        if (v[j] <= pivot)
        {
            i++;
            swap(&v[i], &v[j]);
        }
    swap(&v[i+1], &v[dr]);
    return i+1;
}

int partitionare_randomizata(int v[], int st, int dr)
{
    int r = rand() % (dr - st + 1) + st;
    swap(&v[r], &v[dr]);
    return partitionare(v, st, dr);
}

void QuickSort(int v[], int st, int dr)
{
    if (st >= dr)
        return;
    int q = partitionare_randomizata(v, st, dr);
    QuickSort(v, st, q-1);
    QuickSort(v, q+1, dr);
}

int main()
{
    int n;
    int v[100];
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
        scanf("%d", &v[i]);
    QuickSort(v, 0, n-1);

    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    return 0;
}
