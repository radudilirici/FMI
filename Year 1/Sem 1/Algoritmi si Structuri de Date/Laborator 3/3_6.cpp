#include <iostream>
#include <stdio.h>

using namespace std;

struct nod
{
    int val, indice;
    nod *urm;
};

void afisare(nod *p)
{
    while (p)
    {
        printf("indice: %d  valoare: %d\n", p->indice, p->val);
        p=p->urm;
    }
}

void adaugare_final(nod *&p, nod *&u, int valcrt, int indicecrt)
{
    if (p==NULL)
    {
        p=new nod;
        p->val=valcrt;
        p->indice=indicecrt;
        p->urm=NULL;
        u=p;
        return;
    }
    nod *a=new nod;
    a->val=valcrt;
    a->indice=indicecrt;
    a->urm=NULL;
    u->urm=a;
    u=a;
}

void citire(nod *&p, nod *&u)
{
    int n, val, indice=0;
    scanf("%d", &n);
    for (int i=1; i<=n; i++)
    {
        scanf("%d", &val);
        if (val!=0)
            adaugare_final(p, u, val, indice);
        indice++;
    }
}

nod *suma(nod *p, nod *q)
{
    nod *a=NULL, *b=NULL;
    int i, j;
    while (p && q)
    {
        i=p->indice;
        j=q->indice;
        if (i==j)
        {
            if (p->val+q->val!=0)
                adaugare_final(a, b, p->val+q->val, i);
            p=p->urm;
            q=q->urm;
        }
        else if (i<j)
        {
            if (p->val+q->val!=0)
                adaugare_final(a, b, p->val, i);
            p=p->urm;
        }
        else
        {
            if (p->val+q->val!=0)
                adaugare_final(a, b, q->val, j);
            q=q->urm;
        }
    }
    while (p)
    {
        adaugare_final(a, b, p->val, p->indice);
        p=p->urm;
    }
    while (q)
    {
        adaugare_final(a, b, q->val, q->indice);
        q=q->urm;
    }
    return a;
}

nod *inmultire_scalara(nod *p, nod *q)
{
    nod *a=NULL, *b=NULL;
    int i, j;
    while (p && q)
    {
        i=p->indice;
        j=q->indice;
        if (i==j && p->val!=0 && q->val!=0)
            adaugare_final(a, b, p->val*q->val, i);
        if (i<=j)
            p=p->urm;
        else
            q=q->urm;
    }
    return a;
}

int main()
{
    nod *p1=NULL, *u1=NULL, *p2=NULL, *u2=NULL, *rez;
    citire(p1, u1);
    citire(p2, u2);

    rez=suma(p1, p2);
    printf("suma:\n");
    afisare(rez);

    rez=inmultire_scalara(p1, p2);
    printf("\nprodus scalar:\n");
    afisare(rez);

    return 0;
}
