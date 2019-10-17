#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f = fopen("input4.txt", "r");

    char s[1000];

    int v[30] = {0};
    int mx = 0;

    int i = 0;
    while (1)
    {
        fscanf(f, "%c", &s[i]);
        if (feof(f))
            break;

        if (s[i] >= 65 && s[i] <= 90)
            s[i] += 32;

        if (s[i] >= 97 && s[i] <= 122)
        {
            v[s[i] - 'a']++;
            if (v[s[i] - 'a'] > mx)
                mx = v[s[i] - 'a'];
        }
        i++;
    }
    s[i] = '\0';

    FILE *g = fopen("output4.txt", "w");

    for (i = 0; i < 26; i++)
        if (v[i] == mx)
            fprintf(g, "%c ", i + 'a');

    return 0;
}
