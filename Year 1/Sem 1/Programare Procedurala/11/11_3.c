#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f = fopen("input3.txt", "r");

    char s[1000];

    int i = 0;
    while (1)
    {
        fscanf(f, "%c", &s[i]);
        if (feof(f))
            break;
        if (s[i] >= 65 && s[i] <= 90)
            s[i] += 32;
        else if (s[i] >= 97 && s[i] <= 122)
            s[i] -= 32;
        i++;
    }
    s[i] = '\0';

    FILE *g = fopen("input3.txt", "w");
    fprintf(g, "%s", s);
    return 0;
}
