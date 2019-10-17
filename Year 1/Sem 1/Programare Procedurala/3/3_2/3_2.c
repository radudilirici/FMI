#include <stdio.h>
#include <stdlib.h>
#include "cod.h"
int main()
{
    int x, y;
    char op;
    scanf("%d %c %d", &x, &op, &y);

    switch (op)
    {
        case '+': printf("%d", suma(x, y)); break;
        case '-': printf("%d", scadere(x, y)); break;
        case '*': printf("%d", inmultire(x, y)); break;
        case '%': printf("%d", rest(x, y)); break;
        case '/':
            if (y==0)
            {
                printf("Fara impartiri la 0!");
                break;
            }
            printf("%d", impartire(x, y)); break;
        default: printf("Operator gresit");
    }
    return 0;
}
