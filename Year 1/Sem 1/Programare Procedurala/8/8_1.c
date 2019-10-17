#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int x = 1;
    unsigned char *a;
    a = (unsigned char*) &x;
    if (*a == 0)
        printf("Big endian");
    else
        printf("Little endian");
    return 0;
}
