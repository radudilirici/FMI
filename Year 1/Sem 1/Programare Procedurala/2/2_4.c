#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adauga(char hexa[], unsigned int *m, unsigned int val)
{
    *m = *m + 1;
    int i;
    for (i=*m; i>0; i--)
        hexa[i] = hexa[i-1];
    if (val<10)
    {
        hexa[0]='0' + val;
        return;
    }
    val -= 10;
    hexa[0]='A' + val;
}

void eliminare_0(char hexa[], unsigned int *m)
{
    while (hexa[0] == '0')
    {
        int i;
        *m = *m - 1;
        for (i=0; i<*m; i++)
            hexa[i]=hexa[i+1];
        hexa[*m] = NULL;
    }
}

int main()
{
    char str[40], hexa[40]={0};
    scanf("%s", &str);
    unsigned int n=strlen(str), m=0, x, p;

    while (n>=4)
    {
        x = (str[n-1]-'0') + (str[n-2]-'0')*2 + (str[n-3]-'0')*4 + (str[n-4]-'0')*8;
        adauga(hexa, &m, x);
        n -= 4;
    }

    p = 1;
    x = 0;

    while (n>0)
    {
        x += (str[n-1]-'0')*p;
        p *= 2;
        n --;
    }
    if (x)
        adauga(hexa, &m, x);

    eliminare_0(hexa, &m);

    printf("%s", hexa);

    return 0;
}
