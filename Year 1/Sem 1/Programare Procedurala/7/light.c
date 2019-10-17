#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f = fopen("windows.bmp", "rb");
    FILE *g = fopen("windows_light.bmp", "wb");

    unsigned char x, y;
    int i;

    for (i=0; i<54; i++)
    {
        fread(&x, 1, 1, f);
        fwrite(&x, 1, 1, g);
    }

    while (fread(&x, 1, 1, f) == 1)
    {
        if (x + 50 > 255)
            y = 255;
        else
            y = x + 50;
        fwrite(&y, 1, 1, g);
    }

    fclose(f);
    fclose(g);

    return 0;
}
