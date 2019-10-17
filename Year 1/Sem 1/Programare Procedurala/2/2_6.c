#include <stdio.h>
#include <stdlib.h>

int main()
{
    int p, i, j, k;
    scanf("%d", &p);

    for (i=1; i<=p-2; i++)
        for (j=1; j<=p-i-1; j++)
        {
            k = p-i-j;
            if (i+j > k && i+k > j && j+k >i)
                printf("%d %d %d\n", i, j, k);
        }
    return 0;
}
