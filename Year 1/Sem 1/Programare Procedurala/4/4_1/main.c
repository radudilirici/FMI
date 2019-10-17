#include <stdio.h>
#include <stdlib.h>
#include "transf.c"

int main()
{
    short int n;
    scanf("%hd", &n);

    n=inversare(n);

    printf("%hd", n);
    return 0;
}
