#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void citire(int v[100])
{
    char s[100];
    scanf("%s", s);
    int i, n = strlen(s);
    for (i=0; i<n; i++)
        v[i] = s[n-i-1] - '0';
    v[i] = -1;
}

void adunare(int x[], int y[], int suma[])
{
    int i = 0, minte = 0, plus;
    while (x[i] != -1 && y[i] != -1)
    {
        plus = x[i] + y[i] + minte;
        minte = 0;
        if (plus >= 10)
        {
            minte += plus / 10;
            plus %= 10;
        }
        suma[i] = plus;
        i++;
    }
    if (x[i] != -1)
        while (x[i] != -1)
        {
            plus = x[i] + minte;
            minte = 0;
            if (plus >= 10)
            {
                minte += plus / 10;
                plus %= 10;
            }
            suma[i] = plus;
            i++;
        }
    else
        while (y[i] != -1)
        {
            plus = y[i] + minte;
            minte = 0;
            if (plus >= 10)
            {
                minte += plus / 10;
                plus %= 10;
            }
            suma[i] = plus;
            i++;
        }
    if (minte)
    {
        suma[i] = minte;
        i++;
    }
    suma[i] = -1;
}

int main()
{
    int x[100], y[100], suma[100];
    citire(x);
    citire(y);
    adunare(x, y, suma);
    int i = 0;
    while (suma[i+1] != -1)
        i++;
    while (i >= 0)
    {
        printf("%d", suma[i]);
        i--;
    }
    return 0;
}
