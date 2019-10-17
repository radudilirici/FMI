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

int P_de_x(pol *p, int x)
{
    int valoare=0;
    while (p)
    {
        int xi=1;
        for (int i=1; i<=p->gr; i++)
            xi*=x;
        xi*=p->coef;
        valoare+=xi;
        p=p->urm;
    }
    return valoare;
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

int main()
{
    int n, val, x;
    pol *p=NULL;
    fscanf(f, "%d", &n);
    for (int i=n; i>=0; i--)
    {
        fscanf(f, "%d", &val);
        adauga(p, i, val);
    }
    fscanf(f, "%d", &x);

    fprintf(g, "%d", P_de_x(p, x));

    return 0;
}
