#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union
{
    int balcon;
    char apartament;
    char casa[31];
}detaliu;

typedef struct
{
    char adresa[101];
    int suprafata;
    char locuinta[31];
    int nr_camere;
    detaliu ceva;
}locuinta;

int main()
{
    locuinta v[101];
    int n, i, k, supr_max;
    scanf("%d", &n);
    for (i=0; i<n; i++)
    {
        scanf("%s %d %s %d", &v[i].adresa, &v[i].suprafata, &v[i].locuinta, &v[i].nr_camere);
        if (strcmp(v[i].locuinta, "casa")==0)
            scanf("%s", &v[i].ceva.casa);
        else if (strcmp(v[i].locuinta, "garsoniera")==0)
            scanf("%d", &v[i].ceva.balcon);
        else if (strcmp(v[i].locuinta, "apartament")==0)
            scanf("%c", &v[i].ceva.apartament);
    }

    supr_max=0;
    k=-1;
    for (i=0; i<n; i++)
    {
        if (strcmp(v[i].locuinta, "garsoniera")==0 && v[i].ceva.balcon==1 && v[i].suprafata > supr_max)
        {
            k=i;
            supr_max=v[i].suprafata;
        }
    }

    if (k>0)
        printf("%s", v[k].adresa);
    else
        printf("Nu exista");

    return 0;
}
