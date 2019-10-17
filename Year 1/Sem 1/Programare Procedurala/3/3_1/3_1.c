#include <stdio.h>
#include <stdlib.h>
#include "cod.h"

int main()
{
    char c;
    scanf("%c", &c);
    printf("%c ", to_lower(c));
    return 0;
}
