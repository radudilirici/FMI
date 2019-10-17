#include <iostream>
#include <stdio.h>

using namespace std;

FILE *f=fopen("data.in", "r");
FILE *g=fopen("data.out", "w");

struct pol
{
    int gr, coef;
    pol *urm;
};

void afisare_inversa(pol *p)
{
    if (p->urm)
        afisare_inversa(p->urm);
    fprintf(g, "%d ", p->coef);
}

void inmultire_scalar(pol *&p, int a)
{
    pol *c=p;
    while (c)
    {
        c->coef*=a;
        c=c->urm;
    }
}

void adauga(pol *&p, int gr1, int coef1)
{
    if (p==NULL)
    {
        p=new pol;
        p->gr=gr1;
        p->coef=coef1;
        p->urm=NULL;
        return;
    }
    if (p->gr>gr1)
    {
        pol *q=new pol;
        q->gr=gr1;
        q->coef=coef1;
        q->urm=p;
        p=q;
        return;
    }
    pol *c=p;
    while (c->urm)
    {
        if (c->urm->gr>gr1)
            break;
        c=c->urm;
    }
    pol *q=new pol;
    q->gr=gr1;
    q->coef=coef1;
    q->urm=c->urm;
    c->urm=q;
}

void suma_pol(pol *&p, pol *q)
{
    pol *c=p;
    while (c->urm && q->urm)
    {
        c->coef+=q->coef;
        c=c->urm;
        q=q->urm;
    }
    c->coef+=q->coef;
    q=q->urm;
    while (q)
    {
        pol *a=new pol;
        a->urm=NULL;
        a->coef=q->coef;
        a->gr=q->gr;
        c->urm=a;
        c=c->urm;
        q=q->urm;
    }
}

int main()
{
    int n, m, val;
    pol *p=NULL, *q=NULL;
    fscanf(f, "%d %d", &n, &m);
    for (int i=n; i>=0; i--)
    {
        fscanf(f, "%d", &val);
        adauga(p, i, val);
    }
    for (int i=m; i>=0; i--)
    {
        fscanf(f, "%d", &val);
        adauga(q, i, val);
    }

    suma_pol(p, q);

    afisare_inversa(p);
    fprintf(g, "\n");
    return 0;
}
