#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,c;
    scanf("%d",&x);
    c=x<<3;
    printf("%d\n",c);
    c=x>>2;
    printf("%d\n",c);
    c=(x<<3)+(x<<1);
    printf("%d\n",c);
    return 0;
}
