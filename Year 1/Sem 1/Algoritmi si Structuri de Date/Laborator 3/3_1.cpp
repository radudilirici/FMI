#include <iostream>
#include <stdio.h>

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
    printf(" ");
}

void adauga(nod *&p, int x)
{
    if (p==NULL)
    {
        p=new nod;
        p->val=x;
        p->urm=NULL;
        return;
    }
    if (p->val>x)
    {
        nod *q=new nod;
        q->val=x;
        q->urm=p;
        p=q;
        return;
    }
    nod *c=p;
    while (c->urm)
    {
        if (c->urm->val>x)
            break;
        c=c->urm;
    }
    nod *q=new nod;
    q->val=x;
    q->urm=c->urm;
    c->urm=q;
}

int main()
{
    int n, x;
    nod *p=NULL;
    scanf("%d",&n);
    for (int i=1; i<=n; i++)
    {
        scanf("%d", &x);
        adauga(p,x);
    }
    afisare(p);
    return 0;
}
