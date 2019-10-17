#include <stdio.h>
#include <stdlib.h>

int parinte(int k)
{
    return (k-1)/2;
}

int fiu_stang(int k)
{
    return (k+1) * 2 - 1;
}

int fiu_drept(int k)
{
    return (k+1) * 2;
}

void shift(int v[], int n, int k)
{
    int fiu;
    do
    {
        fiu = 0;
        if (fiu_stang(k) < n)
        {
            fiu = fiu_stang(k);
            if (v[fiu_drept(k)] < v[fiu] && fiu_drept(k) < n)
                fiu = fiu_drept(k);
            if (v[fiu] > v[k])
                fiu = 0;
            if (fiu)
            {
                int aux = v[fiu];
                v[fiu] = v[k];
                v[k] = aux;
                k = fiu;
            }
        }
    }while (fiu);
}

void decapitare(int v[], int n)
{
    v[0] = v[n-1];
    n--;

    shift(v, n, 0);
}

void heapuire(int v[], int n)
{
    int i;
    for (i = n / 2; i >= 0; i--)
        shift(v, n, i);
}

void heapsort(int v[], int srt[], int n)
{
    int i = 0;
    while (n >= 0)
    {
        srt[i++] = v[0];
        decapitare(v, n);
        n--;
    }
}

void citire(int v[], int n)
{
    int i, x;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &x);
        v[i] = x;
    }
}

int main()
{
    int v[100], srt[100];
    int n;

    scanf("%d", &n);
    citire(v, n);
    heapuire(v, n);

    heapsort(v, srt, n);

    int i;
    for (i = 0; i < n; i++)
        printf("%d ", srt[i]);
    printf("\n");

    return 0;
}
