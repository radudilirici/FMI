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

void a(int x, int n)
{
    x=x>>(n-1);
    printf("%d\n",x&1);
}

void b(int x, int n)
{
    x=x|(1<<(n-1));
    afisare_bin(x);
    printf(" %d\n", x);
}

void c(int x, int n)
{
    int cp=1;
    cp=cp<<(n-1);
    cp=~cp;
    x=x&cp;
    afisare_bin(x);
    printf(" %d\n", x);
}

void d(int x, int n)
{
    int cp=x>>(n-1)&1;
    if (cp==1)
    {
        c(x, n);
    }
    else
    {
        b(x, n);
    }
}

int main()
{
    int x, n;
    scanf("%d %d", &x, &n);

    a(x, n);
    b(x, n);
    c(x, n);
    d(x, n);

    return 0;
}
