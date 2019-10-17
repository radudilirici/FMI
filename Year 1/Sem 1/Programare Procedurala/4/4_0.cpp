#include <stdio.h>

using namespace std;

typedef union
{
    int x;
    double y;
}Test;

int main()
{
    Test t;
    t.x = 0;
    t.y = 3.14;
    printf("\nt.x = %d\nt.y = %f\n\n", t.x, t.y);
    return 0;
}
