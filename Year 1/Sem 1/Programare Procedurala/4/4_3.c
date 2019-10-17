#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned int sub65:1;
    unsigned int norma:1;
    char CNP[14];
    char nume[31];
}info;

int main()
{
    //info persoana;
    printf("%d\n", sizeof(info));
    return 0;
}
