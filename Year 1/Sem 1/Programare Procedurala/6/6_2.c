#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f = fopen("numere_intregi.txt", "r+b");
    FILE *p = fopen("poz.out", "w");
    FILE *neg = fopen("neg.out", "w");

    if (f == NULL || p == NULL || neg == NULL)
    {
        printf("gsadfgafsafhsad");
        return 1;
    }

    int n, i, x, k=20;

    fwrite(&k, sizeof(int), 1, f);

    for (i = 0; i < k; i++)
    {
        x = rand() % (201) - 100;
        printf("%d ", x);
        fwrite(&x, sizeof(int), 1, f);
    }

    fseek(f, 0, SEEK_SET);

    fread(&n, sizeof(int), 1, f);

    for (i = 0; i < n; i++)
    {
        fread(&x, sizeof(int), 1, f);
        if (x > 0)
            fwrite(&x, sizeof(int), 1, p);
        else if (x < 0)
            fwrite(&x, sizeof(int), 1, neg);
    }

    return 0;
}
