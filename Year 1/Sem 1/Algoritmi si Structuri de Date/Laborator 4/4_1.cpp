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

nod *lista_inversa_b(nod *p)
{
    if (p->urm == NULL)
        return p;
    nod *b=NULL, *q=NULL, *c=p; // b e primul element al listei noi, folosim q ca sa adaugam element nou la lista, c e o copie

    while (c->urm != NULL) //b devine inceputul listei B
    {
        q=c; //q e penultimul element al lui A
        c=c->urm;
        b=c;
    }

    b->urm=q;
    q->urm=NULL;

    while (q!=p)
    {
        c=p;
        while (c->urm != q)
            c=c->urm;
        q->urm=c;
        q=c;
        q->urm=NULL;
    }
    return b;
}

void inversare_lista(nod *&p)
{
    nod *prim, *last;
    prim=p->urm;
    last=p;
    prim->urm=last;
    last->urm=NULL;
    p=prim;
}

int main()
{
    nod *p=NULL, *u=NULL, *b;
    citire(p, u);
    b=lista_inversa_b(p);
    afisare(b);
    inversare_lista(p);
    //afisare(p);
    return 0;
}
