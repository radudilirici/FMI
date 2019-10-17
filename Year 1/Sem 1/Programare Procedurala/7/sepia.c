#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f = fopen("windows.bmp", "rb");
    FILE *g = fopen("windows_sepia.bmp", "wb");

    unsigned char x, y, z;
    int i;
    float a, b, c;

    for (i=0; i<54; i++)
    {
        fread(&x, 1, 1, f);
        fwrite(&x, 1, 1, g);
    }

    i = 0;

    while (fread(&x, 1, 1, f) == 1 && fread(&y, 1, 1, f) == 1 && fread(&z, 1, 1, f) == 1)
    {
        c = x;
        b = y;
        a = z;

        float red = (int)(0.393*a + 0.768*b + 0.189*c);
        float green = (int)(0.349*a + 0.686*b + 0.168*c);
        float blue = (int)(0.272*a + 0.534*b + 0.131*c);

        if (red > 255)
            red = 255;

        if (green > 255)
            green = 255;

        if (blue > 255)
            blue = 255;

        x = blue;
        y = green;
        z = red;

        fwrite(&x, 1, 1, g);
        fwrite(&y, 1, 1, g);
        fwrite(&z, 1, 1, g);
    }

    fclose(f);
    fclose(g);

    return 0;
}
