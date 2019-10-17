#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int val;
    int pr;
}nod;

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

void shift(nod v[], int n, int k)
{
    int fiu;
    do
    {
        fiu = 0;
        if (fiu_stang(k) < n)
        {
            fiu = fiu_stang(k);
            if ((v[fiu_drept(k)].pr < v[fiu].pr || (v[fiu_drept(k)].pr == v[fiu].pr && v[fiu_drept(k)].val < v[fiu].val)) && fiu_drept(k) < n)
                fiu = fiu_drept(k);
            if (v[fiu].pr > v[k].pr)
                fiu = 0;
            if (fiu)
            {
                nod aux = v[fiu];
                v[fiu] = v[k];
                v[k] = aux;
                k = fiu;
            }
        }
    }while (fiu);
}

nod maximum(nod q[])
{
    return q[0];
}

nod extract_max(nod v[], int n)
{
    nod a = maximum(v);

    v[0] = v[n-1];
    n--;

    shift(v, n, 0);

    return a;
}

void heapuire(nod v[], int n)
{
    int i;
    for (i = n / 2; i >= 0; i--)
        shift(v, n, i);
}

void insert(nod q[], nod x, int k)
{
    q[k] = x;
}

void heapsort(nod v[], nod q[], int n)
{
    int i = 0;
    nod x;
    while (n >= 0)
    {
        x = extract_max(v, n);
        insert(q, x, i);
        i++;
        n--;
    }
}

void citire(nod v[], int n)
{
    int i, x, pr;
    for (i = 0; i < n; i++)
    {
        scanf("%d %d", &x, &pr);
        v[i].val = x;
        v[i].pr = pr;
    }
}

int main()
{
    nod v[100], q[100];
    int n;

    scanf("%d", &n);
    citire(v, n);
    heapuire(v, n);

    heapsort(v, q, n);

    int i;
    printf("\n");
    for (i = 0; i < n; i++)
        printf("%d %d\n", q[i].val, q[i].pr);
    printf("\n");

    return 0;
}
