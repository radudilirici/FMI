#include <stdio.h>
#include <stdlib.h>

void afisare_bin(int x)
{
    long long i;
    for (i=8*sizeof(int)-1; i>=0; i--)
    {
        printf("%d",x>>i&1);
    }
}

int main()
{
    int x, y, n, p;
    scanf("%d %d %d %d", &x, &y, &n, &p);

    afisare_bin(x);
    printf(" %d\n", x);

    int mask=-1;
    mask=mask<<(p-1);
    mask=~mask;
    x=x&mask;

    afisare_bin(x);
    printf(" %d\n\n", x);

    afisare_bin(y);
    printf(" %d\n", y);

    mask=-1;
    mask=mask<<n;
    mask=~mask;
    y=y&mask;

    afisare_bin(y);
    printf(" %d\n\n", y);

    y=y<<p;
    x+=y;

    afisare_bin(x);
    printf(" %d", x);

    return 0;
}
