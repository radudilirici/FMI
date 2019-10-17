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
    int x;
    scanf("%d",&x);
    afisare_bin(x);
    return 0;
}
