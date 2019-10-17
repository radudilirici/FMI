#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f = fopen("windows.bmp", "rb");
    FILE *g = fopen("windows_blur.bmp", "wb");

    unsigned char v1[3], v2[3], v3[3], x;
    int i;

    for (i=0; i<54; i++)
    {
        fread(&x, 1, 1, f);
        fwrite(&x, 1, 1, g);
    }

    while (fread(v1, 1, 3, f) == 3 && fread(v2, 1, 3, f) == 3 && fread(v2, 1, 3, f) == 3)
    {
        v1[0] = (v1[0] + v2[0] + v3[0])/3;
        v1[1] = (v1[1] + v2[1] + v3[1])/3;
        v1[2] = (v1[2] + v2[2] + v3[2])/3;

        fwrite(v1, 1, 3, g);
        fwrite(v1, 1, 3, g);
        fwrite(v1, 1, 3, g);
    }

    fclose(f);
    fclose(g);

    return 0;
}
