#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void modif(void *x, void *y, int n, void *v, int d)
{
    for (int i = 0; i < n; i++)
        if (memcmp((char*)v + i * d, x, d) == 0)
            memcpy((char*)v + i * d, y, d);
}

int main()
{
    int x = 5, y = 6;
    int v[] = {1, 2, 3, 4, 5, 6, 7, 5, 5, 3};
    int n = 10;
    modif(&x, &y, n, v, sizeof(int));
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    return 0;
}
