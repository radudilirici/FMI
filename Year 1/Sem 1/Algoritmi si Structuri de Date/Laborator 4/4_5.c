#include <stdio.h>
#include <stdlib.h>

int elem_majoritar(int v[], int n)
{
    int i, valcrt=v[0], contor=1;
    for (i=1; i<n; i++)
    {
        if (v[i]==valcrt)
            contor++;
        else
        {
            contor--;
            if (contor<=0)
            {
                valcrt=v[i];
                contor=1;
            }
        }
    }
    contor=0;
    for (i=0; i<n; i++)
        if (valcrt==v[i])
            contor++;
    if (contor >= n/2 + 1)
        return valcrt;
    return -1234567;
}

int main()
{
    int v[10001], n, raspuns;

    scanf("%d", &n);
    int i;
    for (i=0; i<n; i++)
        scanf("%d", &v[i]);

    raspuns=elem_majoritar(v, n);

    if (raspuns == -1234567)
        printf("Nu exista!");
    else
        printf("%d", raspuns);
    return 0;
}
