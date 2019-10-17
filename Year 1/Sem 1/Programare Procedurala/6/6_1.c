#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f = fopen("nume.bin", "r+b");
    if (f == NULL)
        printf("Nu mere...");
    int n, x, i, j, k, a, b;

    scanf("%d", &n);
    k=20;
    for (i=0; i<k; i++)
    {
        x = rand() % (2*n+1) - n;
        printf("%d ", x);
        fwrite(&x, sizeof(int), 1, f);
    }
    printf("\n");

    //a
    for (i=0; i<k-1; i++)
    {
        for (j=i+1; j<k; j++)
        {
            fseek(f, sizeof(int)*i, SEEK_SET);
            fread(&a, sizeof(int), 1, f);
            fseek(f, sizeof(int)*j, SEEK_SET);
            fread(&b, sizeof(int), 1, f);

            if (a > b)
            {
                fseek(f, sizeof(int)*j, SEEK_SET);
                fwrite(&a, sizeof(int), 1, f);
                fseek(f, sizeof(int)*i, SEEK_SET);
                fwrite(&b, sizeof(int), 1, f);
            }
        }
    }

    fseek(f, 0, SEEK_SET);

    for (i=0; i<k; i++)
    {
        fread(&a, sizeof(int), 1, f);
        printf("%d ", a);
    }
    printf("\n");

    //b)

    fseek(f, sizeof(int), SEEK_END);
    i = 0;
    fread(&a, sizeof(int), 1, f); //a == max
    b = a;
    while (b == a && i < k)
    {
        fseek(f, sizeof(int)*(k-i-2), SEEK_SET);
        fread(&b, sizeof(int), 1, f);
        i++;
    }

    printf("\n%d %d", a, i);
    return 0;
}
