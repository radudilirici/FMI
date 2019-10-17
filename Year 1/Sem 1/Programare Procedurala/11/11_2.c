#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f = fopen("input2.txt", "r");
    FILE *g = fopen("output2.txt", "w");

    char c1, c2;
    char s[1000];

    fscanf(f, "%c %c ", &c1, &c2);

    fgets(s, 1000, f);
    int n = strlen(s);

    int i;
    for (i = 0; i < n;)
        if (s[i] == c1)
            s[i] = c2;
        else
            i++;

    //fprintf(g, "%c %c\n", c1, c2);
    fprintf(g, "%s", s);
    return 0;
}
