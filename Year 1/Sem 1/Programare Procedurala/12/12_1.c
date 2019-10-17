#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

char *prefix(char *s, ...)
{
    char *aux = malloc(sizeof(s) + 1);
    char *su;
    va_list par;
    va_start(par, s);
    strcpy(aux, s);
    while ((su = va_arg(par, char*)) != NULL)
    {
        int i = 0;
        while (aux[i] == su[i] && aux[i] != '\0')
            i++;
        aux[i] = '\0';
    }
    va_end(par);
    return aux;
}

int main()
{
    char *a = malloc(100);
    char *b = malloc(100);
    char *c = malloc(100);

    scanf("%s %s %s", a, b, c);
    char *p = prefix(a, b, c, NULL);
    printf("%s\n", p);
    return 0;
}
