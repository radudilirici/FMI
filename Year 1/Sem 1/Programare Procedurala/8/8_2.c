#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int x = 260;
    unsigned char *a;
    a = (unsigned char*) &x;
    printf("%u ", *a);
    a = a+1;
    printf("%u ", *a);
    a = a+1;
    printf("%u ", *a);
    a = a+1;
    printf("%u ", *a);
    return 0;
}
