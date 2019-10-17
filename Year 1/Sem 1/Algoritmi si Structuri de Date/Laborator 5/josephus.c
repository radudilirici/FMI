#include <stdio.h>
#include <stdlib.h>

int main()
{
    int putere, nr;
    char plus;
    printf("n = 2^");
    scanf("%d %c %d", &putere, &plus, &nr);
    printf("%d", 2*nr+1);
    return 0;
}
