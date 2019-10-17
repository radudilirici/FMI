#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c,mx;
    scanf("%d %d %d",&a,&b,&c);
    mx=(a>b && a>c)?a:(b>a && b>c)?b:c;
    printf("%d",mx);
    return 0;
}
