#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

int main()
{
    float a,b,c,d,x1,x2;
    scanf("%f %f %f",&a,&b,&c);
    d=(b*b)-(4*a*c);
    if(d<0)
        printf("Nu exista solutii reale.\n");
    else
    {
        d=sqrt(d);
        x1=(-b-d)/(2*a);
        x2=(-b+d)/(2*a);
        printf("x1=%g\nx2=%g",x1,x2);
    }
    return 0;
}
