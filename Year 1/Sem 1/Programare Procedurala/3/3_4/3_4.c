#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int i, j, val;
}linie;

typedef struct
{
    int nr_c, nr_l;
    linie v[101];
}mtr;

void initializare(mtr matrice[101])
{
    int i, j;
    matrice[0].nr_l=0;
    for (i=0; i<=100; i++)
    {
        matrice[i].nr_c = 0;
        for (j=0; j<=100; j++)
            matrice[i].v[j].i = matrice[i].v[j].j = matrice[i].v[j].val = 0;
    }
}

void afisare(mtr matrice[101])
{
    int i, j;
    for (i=1; i<=matrice[0].nr_l; i++)
    {
        printf("Linia %d: ", matrice[i].v[1].i);
        for (j=1; j<=matrice[i].nr_c; j++)
        {
            printf("j=%d val=%d  ", matrice[i].v[j].j, matrice[i].v[j].val);
        }
        printf("\n");
    }
}

void add(int i, int j, int valcrt, linie v[101])
{
    int pozitie=1;
    while (v[pozitie].j < j && v[pozitie].val != 0)
        pozitie++; //astfel vom ajunge ori la o pozitie libera cand construim matricea, ori in locul in care trebuie sa adaugam in cazul adunarii de matrice
    v[pozitie].i = i;
    v[pozitie].j = j;
    v[pozitie].val += valcrt;
}

void adaugare(mtr matrice1[101], mtr matrice2[101], mtr rezultat[101])
{
    int ln, a, b, k=1, adaugat;
    int poza=0, pozb=0;
    for (ln=1; ln<=100; ln++)
    {
        //a si b sunt "j-urile"
        a=matrice1[ln].v[1].j; //v[poza].j
        b=matrice2[ln].v[1].j; //v[pozb].j
        adaugat=0;
        while (a != 0 && matrice1[ln].v[1].i == ln && b != 0 && matrice2[ln].v[1].i == ln) //cand o sa treaca de ultimul element dintr-o linie, a sau b o sa fie 0
        {
            printf("%d %d\n", a, b);
            if (a < b)
            {
                printf("a\n");
                add(ln, a, matrice1[ln].v[a].val, rezultat[k].v);
                rezultat[k].nr_c++;
                poza++;
                a=matrice1[ln].v[poza].j;
                adaugat=1;
            }
            else if (a > b)
            {
                printf("b\n");
                add(ln, b, matrice1[ln].v[b].val, rezultat[k].v);
                rezultat[k].nr_c++;
                pozb++;
                b=matrice2[ln].v[pozb].j;
                adaugat=1;
            }
            else
            {
                printf("ab\n");
                add(ln, b, matrice1[ln].v[b].val, rezultat[k].v);
                add(ln, a, matrice1[ln].v[a].val, rezultat[k].v);
                rezultat[k].nr_c++;
                poza++;
                pozb++;
                a=matrice1[ln].v[poza].j;
                b=matrice2[ln].v[pozb].j;
                adaugat=1;
            }
        }
        while (a != 0 && matrice1[ln].v[1].i == ln)
        {
            printf("a\n");
            add(ln, a, matrice1[ln].v[a].val, rezultat[k].v);
            rezultat[k].nr_c++;
            poza++;
            a=matrice1[ln].v[poza].j;
            adaugat=1;
        }
        while (b != 0 && matrice2[ln].v[1].i == ln)
        {
            printf("b\n");
            add(ln, b, matrice1[ln].v[b].val, rezultat[k].v);
            rezultat[k].nr_c++;
            pozb++;
            b=matrice2[ln].v[pozb].j;
            adaugat=1;
        }
        if (adaugat)
        {
            k++;
            rezultat[0].nr_l++;
        }
    }
}

void citire(int n, int m, mtr matrice[101])
{
    int i, j, k=1, valcrt, adaugat;
    for (i=1; i<=n; i++)
    {
        adaugat=0; //pentru a nu lasa linii goale
        for (j=1; j<=m; j++)
        {
            scanf("%d", &valcrt);
            if (valcrt != 0)
            {
                add(i, j, valcrt, matrice[k].v);
                matrice[k].nr_c++;
                adaugat=1;
            }
        }
        if (adaugat)
        {
            k++;
            matrice[0].nr_l++; //numarul de linii
        }
    }
}

int main()
{
    int n1, m1, n2, m2;
    mtr matrice1[101], matrice2[101], rezultat[101];
    scanf("%d  %d", &n1, &m1);
    citire(n1, m1, matrice1);
    scanf("%d  %d", &n2, &m2);
    citire(n2, m2, matrice2);

    afisare(matrice1);
    printf("\n");
    afisare(matrice2);
    printf("\n");

    /*int i, j;
    for (i=1; i<=matrice1[0].nr_l; i++)
    {
        for (j=1; j<=matrice1[i].nr_c; j++)
            printf("%d ", matrice1[i].v[j].j);
        printf("\n");
    }*/

    adaugare(matrice1, matrice2, rezultat);

    afisare(rezultat);

    return 0;
}
