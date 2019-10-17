#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct col
{
    int j, val;
    col *link;
};

struct row
{
    int i;
    row *link;
    col *first;
};

void afisare_matrice(row *r)
{
    while (r)
    {
        printf("%d     ", r->i);
        col *c=r->first;
        while (c)
        {
            printf("%d %d   ", c->j, c->val);
            c=c->link;
        }
        r=r->link;
        printf("\n");
    }
}

void adauga_row(row *&r, int i)
{
    if (r==NULL)
    {
        r=new row;
        r->i=i;
        r->first=NULL;
        r->link=NULL;
        return;
    }

    row *c=r, *a;
    while (c->link)
        c=c->link;

    a=new row;
    a->i=i;
    a->first=NULL;
    a->link=NULL;

    c->link=a;
}

void adauga_col(row *&r, int j, int x)
{
    col *c=r->first;
    while (c->link)
        c=c->link;

    col *a=new col;

    a->j=j;
    a->val=x;
    a->link=NULL;

    c->link=a;
}

void adauga_prim(row *&r, int j, int x)
{
    col *a=new col;

    a->j=j;
    a->val=x;
    a->link=NULL;

    r->first=a;
}

void citire_matrice(int n, int  m, row *&r)
{
    int i, j, x, prim;
    row *copie;

    for (i=1; i<=n; i++)
    {
        adauga_row(r, i);

        if (i==1) //cpoia trebuie initializata dupa ce avem r-ul initializat
            copie=r;
        else if (copie->link != NULL)
            copie=copie->link;

        prim=1;
        for (j=1; j<=m; j++)
        {
            scanf("%d", &x);
            if (x==0)
                continue;
            if (prim)
            {
                prim=0;
                adauga_prim(copie, j, x);
            }
            else
            {
                adauga_col(copie, j, x);
            }
        }
    }
}

void adauga_prim_minim_sau_suma(row *&copie, col *&c1, col *&c2)
{
    if (c1->j == c2-> j)
    {
        adauga_prim(copie, c1->j, c1->val+c2->val);
        c1=c1->link;
        c2=c2->link;
        return;
    }
    if (c1->j < c2->j)
    {
        adauga_prim(copie, c1->j, c1->val);
        c1=c1->link;
        return;
    }
    if (c1->j > c2->j)
    {
        adauga_prim(copie, c2->j, c2->val);
        c2=c2->link;
        return;
    }
}

void adauga_minim_sau_suma(row *&copie, col *&c1, col *&c2)
{
    if (c1->j == c2-> j)
    {
        adauga_col(copie, c1->j, c1->val+c2->val);
        c1=c1->link;
        c2=c2->link;
        return;
    }
    if (c1->j < c2->j)
    {
        adauga_col(copie, c1->j, c1->val);
        c1=c1->link;
        return;
    }
    if (c1->j > c2->j)
    {
        adauga_col(copie, c2->j, c2->val);
        c2=c2->link;
        return;
    }
}

void adunare_matrice(row *r1, row *r2, row *&suma)
{
    row *copie;
    int prim;

    while (r1 && r2)
    {
        adauga_row(suma, r1->i);

        if (r1->i==1)
            copie=suma;
        else if (copie->link != NULL)
            copie=copie->link;

        prim=1;

        col *c1=r1->first, *c2=r2->first;

        while (c1 && c2)
        {
            if (prim)
            {
                prim=0;
                adauga_prim_minim_sau_suma(copie, c1, c2);
            }
            else
                adauga_minim_sau_suma(copie, c1, c2);
        }

        while (c1)
        {
            if (prim)
            {
                prim=0;
                adauga_prim(copie, c1->j, c1->val);
            }
            else
                adauga_col(copie, c1->j, c1->val);

            c1=c1->link;
        }
        while (c2)
        {
            if (prim)
            {
                prim=0;
                adauga_prim(copie, c2->j, c2->val);
            }
            else
                adauga_col(copie, c2->j, c2->val);

            c2=c2->link;
        }

        r1=r1->link;
        r2=r2->link;
    }

    while (r1)
    {
        adauga_row(suma, r1->i);

        if (r1->i==1)
            copie=suma;
        else if (copie->link != NULL)
            copie=copie->link;

        prim=1;

        col *c1=r1->first;

        while (c1)
        {
            if (prim)
            {
                prim=0;
                adauga_prim(copie, c1->j, c1->val);
            }
            else
                adauga_col(copie, c1->j, c1->val);

            c1=c1->link;
        }
        r1=r1->link;
    }

    while (r2)
    {
        adauga_row(suma, r2->i);

        if (r2->i==1)
            copie=suma;
        else if (copie->link != NULL)
            copie=copie->link;

        prim=1;

        col *c2=r2->first;

        while (c2)
        {
            if (prim)
            {
                prim=0;
                adauga_prim(copie, c2->j, c2->val);
            }
            else
                adauga_col(copie, c2->j, c2->val);

            c2=c2->link;
        }
        r2=r2->link;
    }
}

int main()
{
    row *p1=NULL, *p2=NULL, *suma=NULL;
    int n1, m1, n2, m2;

    scanf("%d %d", &n1, &m1);
    citire_matrice(n1, m1, p1);

    scanf("%d %d", &n2, &m2);
    citire_matrice(n2, m2, p2);

    adunare_matrice(p1, p2, suma);

    afisare_matrice(p1);
    printf("\n");
    afisare_matrice(p2);
    printf("\n");
    afisare_matrice(suma);
    return 0;
}
