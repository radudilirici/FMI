#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct nod
{
    int val;
    nod *urm;
};

void afisare(nod *p)
{
    while (p)
    {
        printf("%d ", p->val);
        p=p->urm;
    }
    printf("\n");
}

void adaugare_final(nod *&p, nod *&u, int valcrt)
{
    if (p==NULL)
    {
        p=new nod;
        p->val=valcrt;
        p->urm=NULL;
        u=p;
        return;
    }
    nod *a=new nod;
    a->val=valcrt;
    a->urm=NULL;
    u->urm=a;
    u=a;
}

void adaugare_inceput(nod *&p, int valcrt)
{
    nod *a=new nod;
    a->val=valcrt;
    a->urm=p;
    p=a;
}

void citire(nod *&p, nod *&u)
{
    int n, val;
    scanf("%d", &n);
    for (int i=1; i<=n; i++)
    {
        scanf("%d", &val);
        adaugare_final(p, u, val);
    }
}

void interclasare(nod *&a, nod *b)
{
    /// "a" va fi lista finala
    nod *c=a, *aux, *aux2;

    while (b->val < c->val && b)
    {
        adaugare_inceput(c, b->val);
        b=b->urm;
    }
    a=c; //c este acum primul nod
    while (b && c->urm)
    {
        if (b->val < c->urm->val)
        {
            aux=c->urm;
            aux2=b->urm;
            c->urm=b;
            b->urm=aux;
            c=b;
            b=aux2;
        }
        else
        {
            c=c->urm;
        }
    }
    while (b)
    {
        c->urm=b;
        c=b;
        b=b->urm;
    }
}

int main()
{
    nod *p1=NULL, *u1, *p2=NULL, *u2;
    citire(p1, u1);
    citire(p2, u2);
    interclasare(p1, p2);
    afisare(p1);
    return 0;
}
