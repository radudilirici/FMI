#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f = fopen("input1.txt", "r");
    FILE *g = fopen("input1.txt", "a");

    char c;
    char s[1000];

    fscanf(f, "%c ", &c);
    fgets(s, 1000, f);
    int n = strlen(s);

    int i;
    for (i = 0; i < n;)
        if (s[i] == c)
            strcpy(&s[i], &s[i+1]);
        else
            i++;

    fseek(g, 0, SEEK_END);
    fprintf(g, "%s", s);
    return 0;
}
