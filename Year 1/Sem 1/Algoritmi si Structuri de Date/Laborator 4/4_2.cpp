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

nod *interclasare(nod *a, nod *b)
{
    nod *c=NULL, *cu=NULL;
    while (a && b)
    {
        if (a->val < b->val)
        {
            adaugare_final(c, cu, a->val);
            a=a->urm;
        }
        else
        {
            adaugare_final(c, cu, b->val);
            b=b->urm;
        }
    }
    while (a)
    {
        adaugare_final(c, cu, a->val);
        a=a->urm;
    }
    while (b)
    {
        adaugare_final(c, cu, b->val);
        b=b->urm;
    }
    return c;
}

int main()
{
    nod *p1=NULL, *u1, *p2=NULL, *u2, *c;
    citire(p1, u1);
    citire(p2, u2);
    c=interclasare(p1, p2);
    afisare(c);
    return 0;
}
