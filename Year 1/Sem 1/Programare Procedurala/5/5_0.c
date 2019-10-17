#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[10];
    a[0]=123;
    a[1]=234;
    printf("%d",*(a+120));
    return 0;
}
