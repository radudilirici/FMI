#include <stdio.h>
#include <stdlib.h>

int suma_cifre(int x)
{
    int c = 0;
    while (x)
    {
        c += x%10;
        x /= 10;
    }
    return c;
}

int main()
{
    int x, y;
    scanf("%d %d", &x, &y);
    if (x == 0)
        return 0;
    while (y != 0)
    {
        if (x % suma_cifre(x) == y)
            printf("%d %d\n", x, y);
        x = y;
        scanf("%d", &y);
    }
    return 0;
}
