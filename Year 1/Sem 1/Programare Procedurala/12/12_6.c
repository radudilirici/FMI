#include <stdio.h>
#include <stdlib.h>

int pali(int numar, int *inv, int copie)
{
    if (copie == 0)
    {
        if (numar == *inv)
            return 1;
        return 0;
    }

    *inv = *inv * 10 + copie % 10;
    return pali(numar, inv, copie / 10);
}

int palindrom(int x)
{
    int y = 0;
    return pali(x, &y, x);
}

int main()
{
    int x = 1234321;
    printf("%d\n", palindrom(x));
    return 0;
}
