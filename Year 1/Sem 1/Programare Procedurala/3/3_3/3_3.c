#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nota_trecere 5
#define medie(nota_mate, nota_info, nota_bac) ((((nota_mate)+(nota_info))/2*8)+(nota_bac*2))/10

typedef struct
{
    int nr_legitimatie;
    char nume[10];
    float nota_mate, nota_info, nota_bac, medie;
    unsigned int admis:1;
    int buget:2;
}candidat;

void afisare_toti(candidat v[], int n)
{
    int i;
    for (i=0; i<n; i++)
    {
        printf("Nume: %10s ", v[i].nume);
        printf("Medie: %5g ", v[i].medie);
        printf("Admis: %s ", (v[i].admis==1? "Y":"N"));
        printf("Buget: %s\n", (v[i].buget>0? "Y":"N"));
    }
}

void afisare_dupa_status(candidat v[], int n, int status_admis)
{
    candidat b[101];
    int i, j, nb=0, k;
    float maxim;

    for (i=0; i<n; i++)
        if (v[i].buget == status_admis) //ne intereseaza doar o categorie
            b[nb++]=v[i];


    for (i=0; i<nb-1; i++)
    {
        maxim=b[i].medie;
        k=i;
        for (j=i+1; j<nb; j++)
        {
            if (b[j].medie > maxim)
            {
                maxim=b[j].medie;
                k=j;
            }
        }

        candidat aux=b[i];
        b[i]=b[k];
        b[k]=aux;
    }

    for (i=0; i<nb; i++)
    {
        printf("Nume: %10s ", b[i].nume);
        printf("Medie: %5g ", b[i].medie);
        printf("Admis: %s ", (b[i].admis==1? "Y":"N"));
        printf("Buget: %s\n", (b[i].buget>0? "Y":"N"));
    }
}

void adaugare(candidat v[], int nrcrt)
{
    candidat c1;
    scanf("%d %10s %f %f %f", &c1.nr_legitimatie, &c1.nume, &c1.nota_mate, &c1.nota_info, &c1.nota_bac);

    c1.medie=medie(c1.nota_mate, c1.nota_info, c1.nota_bac);
    c1.admis= (c1.medie >= nota_trecere && c1.nota_mate >= nota_trecere && c1.nota_info >= nota_trecere && c1.nota_bac >= nota_trecere);

    int i=0, j;
    while (i < nrcrt-1 && strcmp(c1.nume, v[i].nume) > 0)
        i++;

    if (i >= nrcrt-1)
    {
        v[i]=c1;
        return;
    }

    for (j=nrcrt-1; j>=i+1; j--)
        v[j]=v[j-1];
    v[i]=c1;
}

void completare_buget(candidat v[], int n)
{
    int i, j, k, minim, nr_admisi=0, nr_buget;
    int origine[101]={0};

    for (i=0; i<n; i++)
        if (v[i].admis == 1)
            nr_admisi++;

    nr_buget=nr_admisi*3/4;

    candidat b[101];
    for (i=0; i<n; i++)
    {
        b[i]=v[i];
        origine[i]=i;
    }

    for (i=0; i<n-1; i++)
    {
        if (b[i].admis == 0)
            continue;

        for (j=i+1; j<n; j++) //vrem ca primii sa fie cei care nu au intrat, indiferent de media finala
        {
            if (b[j].admis == 0)
            {
                int a=origine[i];
                origine[i]=origine[j];
                origine[j]=a;

                candidat aux=b[i];
                b[i]=b[j];
                b[j]=aux;
                break;
            }

        }
    }

    for (i=n-nr_admisi; i<n-1; i++)
    {
        minim=b[i].medie;
        k=i;
        for (j=i+1; j<n; j++) //in mijloc se vor afla cei de la taxa, iar la final cei de la buget
        {
            if (b[j].medie < minim)
            {
                minim=b[j].medie;
                k=j;
            }

        }
        int a=origine[i];
        origine[i]=origine[k];
        origine[k]=a;

        candidat aux=b[i];
        b[i]=b[k];
        b[k]=aux;
    }

    for (i=0; i<n-nr_admisi; i++)
        v[origine[i]].buget=-1;

    for (i=n-nr_admisi; i<n-nr_buget; i++)
        v[origine[i]].buget=0;

    for (i=n-nr_buget; i<n; i++)
        v[origine[i]].buget=1;
}

int main()
{
    candidat v[101];
    int n, i, optiune;

    scanf("%d", &n);
    for (i=1; i<=n; i++)
        adaugare(v, i);

    completare_buget(v, n);

    printf("\n\nOptiuni:\n1 Alfabetic\n2 Buget\n3 Taxa\n4 Respinsi\n\n");
    scanf("%d", &optiune);

    switch(optiune)
    {
        case 1: afisare_toti(v, n); break;
        case 2: afisare_dupa_status(v, n, 1); break;
        case 3: afisare_dupa_status(v, n, 0); break;
        case 4: afisare_dupa_status(v, n, -1); break;
        default: printf("Optiune invalida\n"); break;
    }

    //for (i=0; i<n; i++)
    //    printf("%d %s %g %g %g %g %d %d\n", v[i].nr_legitimatie, v[i].nume, v[i].nota_mate, v[i].nota_info, v[i].nota_bac, v[i].medie, v[i].admis, v[i].buget);

    return 0;
}
